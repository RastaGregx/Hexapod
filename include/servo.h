#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

/**
 * @brief Controller to set all servos to a specified 0–360° position via terminal
 */
class ServoController {
public:
    /**
     * @brief Construct a ServoController for a given I2C address
     * @param address PCA9685 I2C address (default 0x40)
     */
    ServoController(uint8_t address = 0x40);

    /**
     * @brief Initialize PCA9685 and set PWM frequency (50 Hz)
     */
    void begin();

    /**
     * @brief Read serial input and set all servos to the given angle
     *        Command format: <angle>\n where angle is 0..360
     */
    void processSerialCommands();

private:
    Adafruit_PWMServoDriver _pwm;
    uint8_t _address;
    String _input;

    static constexpr uint16_t SERVOMIN = 150;  // Min pulse length out of 4096
    static constexpr uint16_t SERVOMAX = 600;  // Max pulse length out of 4096

    /**
     * @brief Set all channels to the specified 0–360° angle
     * @param angle Angle in degrees (0–360)
     */
    void setAllAngle(uint16_t angle);
};
