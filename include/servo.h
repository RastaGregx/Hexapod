#pragma once
#include <Adafruit_PWMServoDriver.h> 
#include <Wire.h> 

void setupServo();
void setServoPosition(Adafruit_PWMServoDriver& pwm, int channel, int degree);
void relaxServo(Adafruit_PWMServoDriver& pwm, int channel);
void smoothSetServoPosition(Adafruit_PWMServoDriver& pwm, int channel, int &currentPos, int targetPos, int stepDelay, float stepSize, bool relaxAfter);
void moveRestPostion();
void standUp();
void testServo();
void forward();
void backward();
void resumeServo(Adafruit_PWMServoDriver& pwm, int channel, int degree);
void testServoInteractive();
void rotateLeft();
void rotateRight();


struct Leg {
    int hipPin, kneePin, footPin, hipAngle, kneeAngle, footAngle;
};

extern Leg legs[6]; 
