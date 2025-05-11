#include "i2c_verify.h"
#include <Wire.h>
#include <Arduino.h>

void scanI2CBus() {
    SerialUSB.println("Scanning I2C bus...");
    byte error, address;
    int nDevices = 0;

    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            SerialUSB.print("Found I2C device at address 0x");
            if (address < 16) SerialUSB.print("0"); 
            SerialUSB.println(address, HEX);
            nDevices++;
        } else if (error == 4) {
            SerialUSB.print("Unknown error at address 0x");
            if (address < 16) SerialUSB.print("0");
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
}
