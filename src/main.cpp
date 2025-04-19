#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);  // Default I2C address

// These values depend on your servo. For standard servos:
#define SERVOMIN  150  // Pulse for 0 degrees
#define SERVOMAX  600  // Pulse for 180 degrees

void setup() {
  Wire.begin();  // Start I2C communication
  pwm.begin();   // Initialize PCA9685
  pwm.setPWMFreq(50);  // 50 Hz for analog servos

  SerialUSB.begin(115200);  // Serial communication for debug
  while (!SerialUSB);       // Wait for Serial to be ready
  SerialUSB.println("PCA9685 All Servos at Default Position (0°)");

  // Set all servos to default position (0°)
  for (int i = 0; i < 16; i++) {  // Loop through all 16 channels
    pwm.setPWM(i, 0, SERVOMIN);   // Send PWM signal to each servo on all channels
  }
}

void loop() {
  SerialUSB.println("All servos are at the default position (0°).");
  delay(1000);  // Wait a bit before repeating
}
