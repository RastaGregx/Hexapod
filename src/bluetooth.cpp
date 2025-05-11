#include <Arduino.h>
#include <bluetooth.h>

// Assume these are defined and updated elsewhere in your code:
extern float temperature_aht;
extern float relative_humidity;
extern float temperature_bmp;
extern float pressure_hpa;

void sendBluetoothData(float temperature_aht, float relative_humidity, float temperature_bmp, float pressure_hpa) {
  // --- Send Data over Bluetooth (Serial1) ---
  // Format: T_AHT:value,H:value,T_BMP:value,P:value\n
  Serial1.print("T_AHT:");
  Serial1.print(temperature_aht, 1);
  Serial1.print(",H:");
  Serial1.print(relative_humidity, 0);
  Serial1.print(",T_BMP:");
  Serial1.print(temperature_bmp, 1); 
  Serial1.print(",P:");
  Serial1.print(pressure_hpa, 0);
  Serial1.println(); // Send newline to mark end of message

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

  delay(2000);
}
