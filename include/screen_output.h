#pragma once

#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>

void readAndDisplaySensors(Adafruit_AHTX0 &aht, Adafruit_BMP280 &bmp, LiquidCrystal_I2C &lcd);
