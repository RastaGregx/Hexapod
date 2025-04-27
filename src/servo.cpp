#include "servo.h"

ServoController::ServoController(uint8_t address)
    : _pwm(address, Wire), _address(address) {}

void ServoController::begin() {
    Wire.begin();
    _pwm.begin();
    _pwm.setPWMFreq(50);               // Standard 50 Hz for servos
    setAllAngle(0);                    // Initialize to 0°
    Serial.println("ServoController initialized. Enter angle 0-360:");
}

void ServoController::processSerialCommands() {
    while (Serial.available()) {
        char c = Serial.read();
        if (c == '\n') {
            int angle = _input.toInt();
            if (angle >= -100 && angle <= 360) {
                setAllAngle((uint16_t)angle);
                Serial.print("Set all servos to ");
                Serial.print(angle);
                Serial.println("°");
            } else {
                Serial.println("Invalid angle. Enter 0-360.");
            }
            _input = "";  // clear buffer
        } else if (c != '\r') {
            _input += c;
        }
    }
}

void ServoController::setAllAngle(uint16_t angle) {
    // Map 0–360° into SERVOMIN–SERVOMAX pulse range
    uint16_t pulse = SERVOMIN + (uint32_t)(SERVOMAX - SERVOMIN) * angle / 360;
    pulse = constrain(pulse, SERVOMIN, SERVOMAX);
    for (uint8_t ch = 0; ch < 16; ++ch) {
        _pwm.setPWM(ch, 0, pulse);
    }
}