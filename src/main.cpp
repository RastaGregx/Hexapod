#include <Wire.h>
#include <Adafruit_PWMServoDriver.h> // Keep if you plan to use servos later
#include <LiquidCrystal_I2C.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>

// Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);  // Default I2C address (Keep commented if not used yet)

// // These values depend on your servo. For standard servos: (Keep commented if not used yet)
// #define SERVOMIN  150  // Pulse for 0 degrees
// #define SERVOMAX  600  // Pulse for 180 degrees

LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust I2C address if necessary
Adafruit_AHTX0 aht;
Adafruit_BMP280 bmp; // I2C mode

// Define Serial1 for Hardware Serial on pins PA10 (RX) and PA9 (TX)
HardwareSerial Serial1(PA10, PA9); // RX, TX for Bluetooth HC-05

#define BLUETOOTH_BAUD_RATE 9600 // Default baud rate for HC-05, change if needed

void setup() {
  // Start SerialUSB for debugging (if connected to computer)
  SerialUSB.begin(115200);
  unsigned long startTime = millis();
  // Wait maximum 5 seconds for SerialUSB to connect
  while (!SerialUSB && (millis() - startTime < 5000)); 

  SerialUSB.println("System Setup Starting...");

  // -------------- Initialize I2C --------------
  Wire.begin(); // Start I2C

  // -------------- I2C Scanner (Optional - Can be commented out after checking) --------------
  SerialUSB.println("Scanning I2C bus...");
  byte error, address;
  int nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      SerialUSB.print("Found I2C device at address 0x");
      SerialUSB.println(address, HEX);
      nDevices++;
    } else if (error == 4) {
      SerialUSB.print("Unknown error at address 0x");
      SerialUSB.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    SerialUSB.println("No I2C devices found!");
  } else {
    SerialUSB.print("Found ");
    SerialUSB.print(nDevices);
    SerialUSB.println(" I2C device(s).");
  }
  SerialUSB.println("I2C Scan Complete.");
  // ---------------------------------------------------------------------------------------

  //------------ Initialize the LCD --------------
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.print("Initializing...");
  SerialUSB.println("Initializing LCD...");

  //------------ Initialize AHT20 Sensor --------------
  if (!aht.begin()) {
    SerialUSB.println("Error: Could not find AHT20 sensor!");
    lcd.clear();
    lcd.print("AHT20 Error!");
    while (1) delay(10);
  } else {
     SerialUSB.println("AHT20 Sensor Initialized.");
  }

  //------------ Initialize BMP280 Sensor --------------
  // Try both common addresses 0x76 and 0x77
  if (!bmp.begin(0x76) && !bmp.begin(0x77)) { 
    SerialUSB.println("Error: Could not find BMP280 sensor!");
    lcd.clear();
    lcd.print("BMP280 Error!");
    while (1) delay(10);
  } else {
     SerialUSB.println("BMP280 Sensor Initialized.");
  }

  // ------------ Initialize Bluetooth Serial (Serial1) --------------
  Serial1.begin(BLUETOOTH_BAUD_RATE);
  SerialUSB.print("Initializing Bluetooth HC-05 on Serial1 at ");
  SerialUSB.print(BLUETOOTH_BAUD_RATE);
  SerialUSB.println(" baud...");
  Serial1.println("HC-05 Ready!"); // Send a test message over Bluetooth
  delay(100); // Short delay for stability
  SerialUSB.println("Bluetooth Initialized.");
  // ---------------------------------------------------------------

  // ------------ Initialize Servo Driver (Keep commented if not used yet) --------
  // Wire.begin();   // Start I2C communication (already started above)
  // pwm.begin();    // Initialize PCA9685
  // pwm.setPWMFreq(50); // 50 Hz for analog servos
  // SerialUSB.println("PCA9685 Servo Driver Initialized.");
  // SerialUSB.println("PCA9685 All Servos at Default Position (0°)");
  // // Set all servos to default position (0°)
  // for (int i = 0; i < 16; i++) {  // Loop through all 16 channels
  //   pwm.setPWM(i, 0, SERVOMIN);   // Send PWM signal to each servo on all channels
  // }
  // -----------------------------------------------------------------------------

  lcd.clear();
  lcd.print("Setup Complete!");
  SerialUSB.println("System Setup Complete.");
  delay(1000); // Show setup message briefly
}

void loop() {
  // --- Read Sensor Data ---
  sensors_event_t humidity_event, temp_aht_event;
  // Check if sensors are available before reading
  if (!aht.getEvent(&humidity_event, &temp_aht_event)) {
      SerialUSB.println("Error reading AHT sensor!");
      // Handle error appropriately, maybe display on LCD or skip update
      delay(1000);
      return; 
  }

  float temperature_aht = temp_aht_event.temperature;
  float relative_humidity = humidity_event.relative_humidity;
  float temperature_bmp = bmp.readTemperature();
  float pressure_pa = bmp.readPressure(); // Pressure in Pascals
  float pressure_hpa = pressure_pa / 100.0F; // Convert to hPa

  // --- Display Data on LCD ---
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature_aht, 1); // AHT temperature with 1 decimal place
  lcd.print((char)223); // Degree symbol
  lcd.print("C ");

  lcd.setCursor(8, 0); // Position for Pressure
  lcd.print("P:");
  lcd.print(pressure_hpa, 0); // Pressure in hPa, 0 decimal places
  // lcd.print("hPa"); // Uncomment if space allows

  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(relative_humidity, 0); // Humidity with 0 decimal places
  lcd.print("%");

  // --- Send Data over Bluetooth (Serial1) ---
  // Format: T_AHT:value,H:value,T_BMP:value,P:value\n
  Serial1.print("T_AHT:");
  Serial1.print(temperature_aht, 1);
  Serial1.print(",H:");
  Serial1.print(relative_humidity, 0);
  Serial1.print(",T_BMP:"); // Sending BMP temp too, even if not on LCD
  Serial1.print(temperature_bmp, 1); 
  Serial1.print(",P:");
  Serial1.print(pressure_hpa, 0);
  Serial1.println(); // Send a newline character to mark end of message

  // --- Print Data to SerialUSB for Debugging ---
  SerialUSB.print("Sent via BT -> ");
  SerialUSB.print("T_AHT:");
  SerialUSB.print(temperature_aht, 1);
  SerialUSB.print(" C, H:");
  SerialUSB.print(relative_humidity, 0);
  SerialUSB.print(" %, T_BMP:");
  SerialUSB.print(temperature_bmp, 1);
  SerialUSB.print(" C, P:");
  SerialUSB.print(pressure_hpa, 0);
  SerialUSB.println(" hPa");

  // --- Optional Servo Control Code (Keep commented if not used yet) ---
  // SerialUSB.println("All servos are at the default position (0°).");
  // --------------------------------------------------------------------

  delay(2000); // Update interval
}