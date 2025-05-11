#include <Arduino.h>
#include <header.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>


// LCD I2C Address: 0x27 
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Sensor I2C Addresses: AHT20 (0x38), BMP280 (0x77)
Adafruit_AHTX0 aht;
Adafruit_BMP280 bmp; // I2C mode

// Bluetooth HC-05 Serial Communication
HardwareSerial Serial1(PA10, PA9); // RX, TX for Bluetooth HC-05
#define BLUETOOTH_BAUD_RATE 9600 // Default baud rate for HC-05, change if needed

// Timing for the walking cycle
unsigned long previousMillis = 0;
const long interval = 1000;  // Time between each step
String btCommand = "";


void setup() {

  // -------------- System Setup --------------
  SerialUSB.begin(115200);
  unsigned long startTime = millis();
  // Wait maximum 5 seconds for SerialUSB to connect
  while (!SerialUSB && (millis() - startTime < 5000)); 
  SerialUSB.println("System Setup Starting...");

  // -------------- Initialize I2C --------------
  Wire.begin(); // Start I2C

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
  if (!bmp.begin(0x77)) { 
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

  scanI2CBus(); // Scan I2C bus for connected devices
  SerialUSB.println("I2C Scan Complete.");
  setupServo(); // Initialize servos
  SerialUSB.println("Servos Initialized.");
  moveRestPostion(); 

  lcd.clear();
  lcd.print("Setup Complete!");
  SerialUSB.println("System Setup Complete.");
  delay(5000);

  readAndDisplaySensors(aht, bmp, lcd); 

  standUp(); 
}


void loop() {
  while (Serial1.available()) {
    char c = Serial1.read();

    if (c == '\n' || c == '\r') {
      btCommand.trim(); 

      if (btCommand == "data()") {
        sensors_event_t humidity, tempAHT;
        aht.getEvent(&humidity, &tempAHT);
        float tAHT = tempAHT.temperature;
        float rh   = humidity.relative_humidity;
        float tBMP = bmp.readTemperature();
        float p    = bmp.readPressure() / 100.0;
        sendBluetoothData(tAHT, rh, tBMP, p);
      }

      else if (btCommand == "forward()") {
        Serial1.println("OK: Going forward");
        forward();
      }

      else if (btCommand == "backward()") {
        Serial1.println("OK: Going backward");
        backward();
      }

      else if (btCommand == "rotateLeft()") {
        Serial1.println("OK: Rotating left");
        rotateLeft();
      }

      else if (btCommand == "rotateRight()") {
        Serial1.println("OK: Rotating right");
        rotateRight();
      }

      else {
        Serial1.print("ERR: Unknown command: ");
        Serial1.println(btCommand);
      }

      btCommand = ""; 

    } else {
      btCommand += c; 
      if (btCommand.length() > 32) btCommand = "";
    }
  }


}



