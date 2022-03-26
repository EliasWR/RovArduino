#include <Arduino.h>
#include <ArduinoJson.h>
#include "Communication.h"


void sendToRaspberry(int arg1, int arg2, bool arg3) {
  doc["Temp"] = arg1;
  doc["Pressure"] = arg2;
  doc["Leak"] = arg3;
  
  if (isnan(arg1) || isnan(arg2) || isnan(arg3)) {
    Serial.println(F("Failed to read from sensor!"));
    return;
  }

  // Format the data to serial
  serializeJson(doc, Serial);

  // Sending to Raspberry Pi
  Serial.println();
}