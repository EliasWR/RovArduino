#include <Arduino.h>
#include <ArduinoJson.h>
#include "Communication.h"
#include "Functions.h"  // Remove after testing


void sendToRaspberry(float arg1, int arg2, bool arg3) {
  outDoc["Temp"] = arg1;
  outDoc["Pressure"] = arg2;
  outDoc["Leak"] = arg3;
  
  if (isnan(arg1) || isnan(arg2) || isnan(arg3)) {
    Serial.println(F("Failed to read from sensor!"));
    return;
  }

  // Format the data to serial
  serializeJson(outDoc, Serial);

  // Sending to Raspberry Pi
  Serial.println();
}

void receiveFromRaspberry() {

  String  payload;
  payload = Serial.readStringUntil( '\n' );
  StaticJsonDocument<512> doc;
  deserializeJson(doc, payload);
  if (doc["operation"] == "sequence") {
    setMotorSpeeds(0);
      
  }
  else {
    //setMotorSpeeds(0);
  }
}