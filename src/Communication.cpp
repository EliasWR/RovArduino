#include <Arduino.h>
#include <ArduinoJson.h>
#include "Communication.h"
#include "Functions.h"  // Remove after testing


void sendToRaspberry(float arg1, int arg2, bool arg3) {
  outDoc["Temp"] = arg1;
  outDoc["Pressure"] = arg2;
  outDoc["Leak"] = arg3;
  
  /*
  if (isnan(arg1) || isnan(arg2) || isnan(arg3)) {
    Serial.println(F("Failed to read from sensor!"));
    return;
  }
  */

  // Format the data to serial
  serializeJson(outDoc, Serial);

  // Sending to Raspberry Pi
  Serial.println();
}


void receiveFromRaspberry() {
  bool z1lock; bool z2lock; bool z3lock; bool z4lock;
  bool z5lock; bool z6lock; bool z7lock; bool z8lock;
  String  payload;
  payload = Serial.readStringUntil( '\n' );
  StaticJsonDocument<512> doc;
  deserializeJson(doc, payload);

  // If new values where communicated from Raspberry, update outputs
  setLights(doc["light"]);

  z1lock = doc["locked"][0];
  z2lock = doc["locked"][1];
  z3lock = doc["locked"][2];
  z4lock = doc["locked"][3];
  z5lock = doc["locked"][4];
  z6lock = doc["locked"][5];
  z7lock = doc["locked"][6];
  z8lock = doc["locked"][7];
  
  setMotorSpeeds(doc["runZone"], z1lock, z2lock, z3lock, 
  z4lock, z5lock, z6lock, z7lock, z8lock);
}

