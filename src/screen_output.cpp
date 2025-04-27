#include "screen_output.h"
#include <Arduino.h> // Needed for delay(), SerialUSB.println(), etc.

void readAndDisplaySensors(Adafruit_AHTX0 &aht, Adafruit_BMP280 &bmp, LiquidCrystal_I2C &lcd) {
    sensors_event_t humidity_event, temp_aht_event;

    // --- Read Sensor Data ---
    aht.getEvent(&humidity_event, &temp_aht_event);

    if (!aht.getEvent(&humidity_event, &temp_aht_event)) {
        SerialUSB.println("Error reading AHT sensor!");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("AHT read error!");
        delay(1000);
        return;
    }

    float temperature_aht = temp_aht_event.temperature;
    float relative_humidity = humidity_event.relative_humidity;
    float temperature_bmp = bmp.readTemperature();
    float pressure_hpa = bmp.readPressure() / 100.0F;

    // --- Display Data on LCD ---
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(temperature_aht, 1);
    lcd.print((char)223); // Degree symbol
    lcd.print("C ");

    lcd.setCursor(8, 0);
    lcd.print("P:");
    lcd.print(pressure_hpa, 0);

    lcd.setCursor(0, 1);
    lcd.print("H:");
    lcd.print(relative_humidity, 0);
    lcd.print("%");
}
