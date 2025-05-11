#include <servo.h> // Servo Control Library

// Define the PCA9685 I2C address for controlling servos
Adafruit_PWMServoDriver leftpwm = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver rightpwm = Adafruit_PWMServoDriver(0x41);


// Pinouts and default angles for the legs
Leg leftlegs[3] = {
    {0, 1, 2, 90, 30, 30},   // Leg 1 left front - A1
    {3, 4, 5, 90, 30, 30},   // Leg 2 left middle - B2
    {6, 7, 8, 90, 30, 30},   // Leg 3 left back - A3
};

Leg rightlegs[3] = {
    {15, 14, 13, 90, 30, 30},   // Leg 1 right front - B1
    {12, 11, 10, 90, 30, 30},   // Leg 2 right middle - A2
    { 9,  8,  7, 90, 30, 30},   // Leg 3 right back - B3
};



void setupServo() {
    // Initialize the PCA9685 servo driver
    leftpwm.begin();
    leftpwm.setPWMFreq(60);  // Set frequency to 60 Hz for servos
    rightpwm.begin();
    rightpwm.setPWMFreq(60);
  
  }


void setServoPosition(Adafruit_PWMServoDriver& pwm, int channel, int degree) {
    // Convert angle to pulse width (approx 500-2500us for 0-180 degrees)
    int pulseWidth = map(degree, 0, 180, 500, 2500);
    pwm.writeMicroseconds(channel, pulseWidth);
}

void relaxServo(Adafruit_PWMServoDriver& pwm, int channel) {
    pwm.setPWM(channel, 0, 0); // Typically used to stop signal output
}

void resumeServo(Adafruit_PWMServoDriver& pwm, int channel, int degree) {
    int pulseWidth = map(degree, 0, 180, 500, 2500);
    pwm.writeMicroseconds(channel, pulseWidth);
}


void smoothSetServoPosition(Adafruit_PWMServoDriver& pwm, int channel, int &currentPos, int targetPos, int stepDelay = 10, float stepSize = 1.0, bool relaxAfter = false) {
    if (currentPos == targetPos) return;

    int direction = (targetPos > currentPos) ? 1 : -1;

    for (float pos = currentPos; direction > 0 ? pos <= targetPos : pos >= targetPos; pos += direction * stepSize) {
        int pulseWidth = map((int)pos, 0, 180, 500, 2500);
        pwm.writeMicroseconds(channel, pulseWidth);
        delay(stepDelay);
    }

    currentPos = targetPos;

    if (relaxAfter) {
        relaxServo(pwm, channel); 
    }
}

void moveRestPostion() {
    // Move left legs
    for (int i = 0; i < 3; i++) {
        setServoPosition(leftpwm, leftlegs[i].hipPin, leftlegs[i].hipAngle);
        setServoPosition(leftpwm, leftlegs[i].kneePin, leftlegs[i].kneeAngle);
        setServoPosition(leftpwm, leftlegs[i].footPin, leftlegs[i].footAngle);
    }

    // Move right legs
    for (int i = 0; i < 3; i++) {
        setServoPosition(rightpwm, rightlegs[i].hipPin, rightlegs[i].hipAngle);
        setServoPosition(rightpwm, rightlegs[i].kneePin, rightlegs[i].kneeAngle);
        setServoPosition(rightpwm, rightlegs[i].footPin, rightlegs[i].footAngle);
    }
}

  

  void standUp() {

        setServoPosition(leftpwm, leftlegs[0].hipPin, 95);
        setServoPosition(leftpwm, leftlegs[1].hipPin, 105);
        setServoPosition(leftpwm, leftlegs[2].hipPin, 90);
        setServoPosition(rightpwm, rightlegs[0].hipPin, 75);
        setServoPosition(rightpwm, rightlegs[1].hipPin, 85);
        setServoPosition(rightpwm, rightlegs[2].hipPin, 90);

        

        //Feet position
        setServoPosition(leftpwm, leftlegs[0].footPin, 0);
        setServoPosition(leftpwm, leftlegs[1].footPin, 0);
        setServoPosition(leftpwm, leftlegs[2].footPin, 0);
        setServoPosition(rightpwm, rightlegs[0].footPin, 0);
        setServoPosition(rightpwm, rightlegs[1].footPin, 0);
        setServoPosition(rightpwm, rightlegs[2].footPin, 0);

        delay(2000); // Wait for 1 second
    
        //Knee position
        setServoPosition(leftpwm, leftlegs[0].kneePin, 120);
        setServoPosition(leftpwm, leftlegs[1].kneePin, 120);
        setServoPosition(leftpwm, leftlegs[2].kneePin, 115);
        setServoPosition(rightpwm, rightlegs[0].kneePin, 105);
        setServoPosition(rightpwm, rightlegs[1].kneePin, 115);
        setServoPosition(rightpwm, rightlegs[2].kneePin, 115);

        delay(2000); // Wait for 1 second
        setServoPosition(leftpwm, leftlegs[0].footPin, 30);
        setServoPosition(leftpwm, leftlegs[1].footPin, 30);
        setServoPosition(leftpwm, leftlegs[2].footPin, 30);
        setServoPosition(rightpwm, rightlegs[0].footPin, 30);
        setServoPosition(rightpwm, rightlegs[1].footPin, 30);
        setServoPosition(rightpwm, rightlegs[2].footPin, 30);


        delay(2000); // Wait for 1 second
    
        //Knee position
        setServoPosition(leftpwm, leftlegs[0].kneePin, 170);
        setServoPosition(leftpwm, leftlegs[1].kneePin, 170);
        setServoPosition(leftpwm, leftlegs[2].kneePin, 165);
        setServoPosition(rightpwm, rightlegs[0].kneePin, 155);
        setServoPosition(rightpwm, rightlegs[1].kneePin, 165);
        setServoPosition(rightpwm, rightlegs[2].kneePin, 165);


        delay(2000); // Wait for 1 second
        setServoPosition(leftpwm, leftlegs[0].footPin, 65);
        setServoPosition(leftpwm, leftlegs[1].footPin, 80);
        setServoPosition(leftpwm, leftlegs[2].footPin, 90);
        setServoPosition(rightpwm, rightlegs[0].footPin, 75);
        setServoPosition(rightpwm, rightlegs[1].footPin, 65);
        setServoPosition(rightpwm, rightlegs[2].footPin, 80);

        delay(2000); // Wait for 1 second
    
        //Knee position
        setServoPosition(rightpwm, rightlegs[0].kneePin, 100);
        delay(2000); // Wait for 1 second
        setServoPosition(rightpwm, rightlegs[0].kneePin, 145);
        setServoPosition(rightpwm, rightlegs[1].kneePin, 100);
        delay(2000); // Wait for 1 second
        setServoPosition(rightpwm, rightlegs[1].kneePin, 155);
        setServoPosition(rightpwm, rightlegs[2].kneePin, 100);
        delay(2000); // Wait for 1 second
        setServoPosition(rightpwm, rightlegs[2].kneePin, 155);
        setServoPosition(leftpwm, leftlegs[2].kneePin, 100);
        delay(2000); // Wait for 1 second
        setServoPosition(leftpwm, leftlegs[2].kneePin, 155);
  }

void forward() {
    int delayMs = 1000;

    // === Lift Tripod A: L0, R1, L2 ===
    setServoPosition(leftpwm, leftlegs[0].kneePin, 100);
    setServoPosition(rightpwm, rightlegs[1].kneePin, 100);
    setServoPosition(leftpwm, leftlegs[2].kneePin, 100);
    delay(delayMs);

    // === Swing Tripod A backward (prep for forward push) ===
    setServoPosition(leftpwm, leftlegs[0].hipPin, 100);   // backward
    setServoPosition(leftpwm, leftlegs[0].footPin, 130);
    setServoPosition(rightpwm, rightlegs[1].hipPin, 80);  // backward (mirrored)
    setServoPosition(rightpwm, rightlegs[1].footPin, 130);
    setServoPosition(leftpwm, leftlegs[2].hipPin, 100);
    setServoPosition(leftpwm, leftlegs[2].footPin, 130);

    // === Push Tripod B (R0, L1, R2) forward ===
    setServoPosition(rightpwm, rightlegs[0].hipPin, 100); // forward (mirrored)
    setServoPosition(leftpwm, leftlegs[1].hipPin, 80);    // forward
    setServoPosition(rightpwm, rightlegs[2].hipPin, 100);
    delay(delayMs);

    // === Put Down Tripod A ===
    setServoPosition(leftpwm, leftlegs[0].kneePin, 155);
    setServoPosition(leftpwm, leftlegs[0].footPin, 55);
    setServoPosition(rightpwm, rightlegs[1].kneePin, 155);
    setServoPosition(rightpwm, rightlegs[1].footPin, 55);
    setServoPosition(leftpwm, leftlegs[2].kneePin, 155);
    setServoPosition(leftpwm, leftlegs[2].footPin, 55);
    delay(delayMs);

    // === Lift Tripod B: R0, L1, R2 ===
    setServoPosition(rightpwm, rightlegs[0].kneePin, 100);
    setServoPosition(leftpwm, leftlegs[1].kneePin, 100);
    setServoPosition(rightpwm, rightlegs[2].kneePin, 100);
    delay(delayMs);

    // === Swing Tripod B backward ===
    setServoPosition(rightpwm, rightlegs[0].hipPin, 80);  // backward (prep)
    setServoPosition(rightpwm, rightlegs[0].footPin, 130);
    setServoPosition(leftpwm, leftlegs[1].hipPin, 100);   // backward (prep)
    setServoPosition(leftpwm, leftlegs[1].footPin, 130);
    setServoPosition(rightpwm, rightlegs[2].hipPin, 80);
    setServoPosition(rightpwm, rightlegs[2].footPin, 130);

    // === Push Tripod A forward ===
    setServoPosition(leftpwm, leftlegs[0].hipPin, 80);    // forward
    setServoPosition(rightpwm, rightlegs[1].hipPin, 100); // forward (mirrored)
    setServoPosition(leftpwm, leftlegs[2].hipPin, 80);    // forward
    delay(delayMs);

    // === Put Down Tripod B ===
    setServoPosition(rightpwm, rightlegs[0].kneePin, 155);
    setServoPosition(rightpwm, rightlegs[0].footPin, 55);
    setServoPosition(leftpwm, leftlegs[1].kneePin, 155);
    setServoPosition(leftpwm, leftlegs[1].footPin, 55);
    setServoPosition(rightpwm, rightlegs[2].kneePin, 155);
    setServoPosition(rightpwm, rightlegs[2].footPin, 55);
    delay(delayMs);
}

void backward() {
    int delayMs = 1000;

    // === Lift Tripod A: L0, R1, L2 ===
    setServoPosition(leftpwm, leftlegs[0].kneePin, 100);
    setServoPosition(rightpwm, rightlegs[1].kneePin, 100);
    setServoPosition(leftpwm, leftlegs[2].kneePin, 100);
    delay(delayMs);

    // === Swing Tripod A forward (prep for backward push) ===
    setServoPosition(leftpwm, leftlegs[0].hipPin, 80);   // forward
    setServoPosition(leftpwm, leftlegs[0].footPin, 130);
    setServoPosition(rightpwm, rightlegs[1].hipPin, 100); // forward (mirrored)
    setServoPosition(rightpwm, rightlegs[1].footPin, 130);
    setServoPosition(leftpwm, leftlegs[2].hipPin, 80);
    setServoPosition(leftpwm, leftlegs[2].footPin, 130);

    // === Push Tripod B (R0, L1, R2) backward ===
    setServoPosition(rightpwm, rightlegs[0].hipPin, 80); // backward (mirrored)
    setServoPosition(leftpwm, leftlegs[1].hipPin, 100);  // backward
    setServoPosition(rightpwm, rightlegs[2].hipPin, 80);
    delay(delayMs);

    // === Put Down Tripod A ===
    setServoPosition(leftpwm, leftlegs[0].kneePin, 155);
    setServoPosition(leftpwm, leftlegs[0].footPin, 55);
    setServoPosition(rightpwm, rightlegs[1].kneePin, 155);
    setServoPosition(rightpwm, rightlegs[1].footPin, 55);
    setServoPosition(leftpwm, leftlegs[2].kneePin, 155);
    setServoPosition(leftpwm, leftlegs[2].footPin, 55);
    delay(delayMs);

    // === Lift Tripod B: R0, L1, R2 ===
    setServoPosition(rightpwm, rightlegs[0].kneePin, 100);
    setServoPosition(leftpwm, leftlegs[1].kneePin, 100);
    setServoPosition(rightpwm, rightlegs[2].kneePin, 100);
    delay(delayMs);

    // === Swing Tripod B forward ===
    setServoPosition(rightpwm, rightlegs[0].hipPin, 100); // forward
    setServoPosition(rightpwm, rightlegs[0].footPin, 130);
    setServoPosition(leftpwm, leftlegs[1].hipPin, 80);    // forward
    setServoPosition(leftpwm, leftlegs[1].footPin, 130);
    setServoPosition(rightpwm, rightlegs[2].hipPin, 100);
    setServoPosition(rightpwm, rightlegs[2].footPin, 130);

    // === Push Tripod A backward ===
    setServoPosition(leftpwm, leftlegs[0].hipPin, 100);   // backward
    setServoPosition(rightpwm, rightlegs[1].hipPin, 80);  // backward (mirrored)
    setServoPosition(leftpwm, leftlegs[2].hipPin, 100);
    delay(delayMs);

    // === Put Down Tripod B ===
    setServoPosition(rightpwm, rightlegs[0].kneePin, 155);
    setServoPosition(rightpwm, rightlegs[0].footPin, 55);
    setServoPosition(leftpwm, leftlegs[1].kneePin, 155);
    setServoPosition(leftpwm, leftlegs[1].footPin, 55);
    setServoPosition(rightpwm, rightlegs[2].kneePin, 155);
    setServoPosition(rightpwm, rightlegs[2].footPin, 55);
    delay(delayMs);
}



void rotateRight() {
    int delayMs = 1000;

    // === Lift Tripod A (L0, R1, L2) ===
    setServoPosition(leftpwm, leftlegs[0].kneePin, 100);
    setServoPosition(rightpwm, rightlegs[1].kneePin, 100);
    setServoPosition(leftpwm, leftlegs[2].kneePin, 100);
    delay(delayMs);

    // === Rotate hips (left tripod pushes backward) ===
    setServoPosition(leftpwm, leftlegs[0].hipPin, 120);  // backward
    setServoPosition(rightpwm, rightlegs[1].hipPin, 120);
    setServoPosition(leftpwm, leftlegs[2].hipPin, 120);
    setServoPosition(rightpwm, rightlegs[0].hipPin, 90); // forward
    setServoPosition(leftpwm, leftlegs[1].hipPin, 90);    // mirrored
    setServoPosition(rightpwm, rightlegs[2].hipPin, 90);
    delay(delayMs);

    // === Put down Tripod A ===
    setServoPosition(leftpwm, leftlegs[0].kneePin, 155);
    setServoPosition(rightpwm, rightlegs[1].kneePin, 155);
    setServoPosition(leftpwm, leftlegs[2].kneePin, 155);
    delay(delayMs);

    // === Lift Tripod B (R0, L1, R2) ===
    setServoPosition(rightpwm, rightlegs[0].kneePin, 100);
    setServoPosition(leftpwm, leftlegs[1].kneePin, 100);
    setServoPosition(rightpwm, rightlegs[2].kneePin, 100);
    delay(delayMs);

    // === Rotate hips (right tripod pushes forward) ===
    setServoPosition(rightpwm, rightlegs[0].hipPin, 120); // forward
    setServoPosition(leftpwm, leftlegs[1].hipPin, 120);    // mirrored
    setServoPosition(rightpwm, rightlegs[2].hipPin, 120);
    setServoPosition(leftpwm, leftlegs[0].hipPin, 90);  // backward
    setServoPosition(rightpwm, rightlegs[1].hipPin, 90);
    setServoPosition(leftpwm, leftlegs[2].hipPin, 90);
    delay(delayMs);

    // === Put down Tripod B ===
    setServoPosition(rightpwm, rightlegs[0].kneePin, 155);
    setServoPosition(leftpwm, leftlegs[1].kneePin, 155);
    setServoPosition(rightpwm, rightlegs[2].kneePin, 155);
    delay(delayMs);
}

void rotateLeft() {
    int delayMs = 1000;

    // === Lift Tripod A (L0, R1, L2) ===
    setServoPosition(leftpwm, leftlegs[0].kneePin, 100);
    setServoPosition(rightpwm, rightlegs[1].kneePin, 100);
    setServoPosition(leftpwm, leftlegs[2].kneePin, 100);
    delay(delayMs);

    // === Rotate hips (left tripod pushes forward) ===
    setServoPosition(leftpwm, leftlegs[0].hipPin, 90);  // forward
    setServoPosition(rightpwm, rightlegs[1].hipPin, 90);
    setServoPosition(leftpwm, leftlegs[2].hipPin, 90);
    setServoPosition(rightpwm, rightlegs[0].hipPin, 120); // backward
    setServoPosition(leftpwm, leftlegs[1].hipPin, 120);   // mirrored
    setServoPosition(rightpwm, rightlegs[2].hipPin, 120);
    delay(delayMs);

    // === Put down Tripod A ===
    setServoPosition(leftpwm, leftlegs[0].kneePin, 155);
    setServoPosition(rightpwm, rightlegs[1].kneePin, 155);
    setServoPosition(leftpwm, leftlegs[2].kneePin, 155);
    delay(delayMs);

    // === Lift Tripod B (R0, L1, R2) ===
    setServoPosition(rightpwm, rightlegs[0].kneePin, 100);
    setServoPosition(leftpwm, leftlegs[1].kneePin, 100);
    setServoPosition(rightpwm, rightlegs[2].kneePin, 100);
    delay(delayMs);

    // === Rotate hips (right tripod pushes backward) ===
    setServoPosition(rightpwm, rightlegs[0].hipPin, 90); // backward
    setServoPosition(leftpwm, leftlegs[1].hipPin, 90);   // mirrored
    setServoPosition(rightpwm, rightlegs[2].hipPin, 90);
    setServoPosition(leftpwm, leftlegs[0].hipPin, 120);  // forward
    setServoPosition(rightpwm, rightlegs[1].hipPin, 120);
    setServoPosition(leftpwm, leftlegs[2].hipPin, 120);
    delay(delayMs);

    // === Put down Tripod B ===
    setServoPosition(rightpwm, rightlegs[0].kneePin, 155);
    setServoPosition(leftpwm, leftlegs[1].kneePin, 155);
    setServoPosition(rightpwm, rightlegs[2].kneePin, 155);
    delay(delayMs);
}



  void testServo() {

    setServoPosition(rightpwm, rightlegs[0].hipPin, 90);
    setServoPosition(rightpwm, rightlegs[1].hipPin, 90);
    setServoPosition(rightpwm, rightlegs[2].hipPin, 90);

    setServoPosition(leftpwm, leftlegs[0].hipPin, 90); //git
    setServoPosition(leftpwm, leftlegs[1].hipPin, 90); //git
    setServoPosition(leftpwm, leftlegs[2].hipPin, 90); //git  
  }

  void testServoInteractive() {
    SerialUSB.println("Enter command (format: [L/R] [legIndex] [jointType] [angle])");
    SerialUSB.println("Joint types: 0=hip, 1=knee, 2=foot");

    while (true) {
        if (SerialUSB.available()) {
            String input = SerialUSB.readStringUntil('\n'); // Waits until newline
            input.trim(); // Remove whitespace
            
            if (input.length() == 0) continue; // Ignore empty lines
            
            char side;
            int legIndex, jointType, angle;
            int parsed = sscanf(input.c_str(), "%c %d %d %d", &side, &legIndex, &jointType, &angle);
            
            if (parsed == 4 && (side == 'L' || side == 'R') && legIndex >= 0 && legIndex < 3 && jointType >= 0 && jointType < 3 && angle >= 0 && angle <= 180) {
                Leg* leg = (side == 'L') ? &leftlegs[legIndex] : &rightlegs[legIndex];
                Adafruit_PWMServoDriver& pwm = (side == 'L') ? leftpwm : rightpwm;

                int pin = (jointType == 0) ? leg->hipPin :
                          (jointType == 1) ? leg->kneePin :
                                             leg->footPin;

                setServoPosition(pwm, pin, angle);
                SerialUSB.println("Command executed.");
            } else {
                SerialUSB.println("Invalid input. Format: L/R 0-2 0-2 0-180");
            }
        }
    }
}
