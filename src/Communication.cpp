/**********************************************************************
 * SUBPROGRAM OF THE ARDUINO UNO CODE FOR COMMUNICATION BETWEEN THE 
 * ARDUINO AND THE RASPBERRY PI
 *********************************************************************/
#include <Arduino.h>
#include <ArduinoJson.h>
#include "Communication.h"
#include "Functions.h"  // Remove after testing

/**
 * Function that handles communication Raspberry Pi. Takes in three arguments
 * with predefined types, and structures the data to JSON format. The JSON strings
 * are serialized and sent to Raspberry Pi.
 * @param arg1  Environment temperature value
 * @param arg2  Environment pressure value
 * @param arg3  Value that indicates if there is leak inside ROV 
 */
void sendToRaspberry(float arg1, float arg2, bool arg3) {
  outDoc["Temp"] = roundNum(arg1, 1);
  outDoc["Depth"] = arg2;
  outDoc["Leak"] = arg3;
  
  // Format the data to serial
  serializeJson(outDoc, Serial);

  // Sending to Raspberry Pi
  Serial.println();
}

/**
 * Function that handles serial data communicated from the Raspberry Pi. First
 * eight function specific bool variables are declared. Those values stores
 * information about which control zones are interlocked. The data is stored to
 * a string variable which is in turn deserialized and loaded into a JSON
 * document. The JSON document data is accessed using keys and stores the values in
 * variables that are then used in function calls for movement and light control.
 */
void receiveFromRaspberry() {
  bool z1lock; bool z2lock; bool z3lock; bool z4lock;
  bool z5lock; bool z6lock; bool z7lock; bool z8lock;

  String  payload;
  payload = Serial.readStringUntil( '\n' );
  StaticJsonDocument<512> doc;
  deserializeJson(doc, payload);

  // If new values where communicated from Raspberry, update outputs
  setLights(doc["light"]);

  runZone = doc["runZone"];
  z1lock = doc["locked"][0];
  z2lock = doc["locked"][1];
  z3lock = doc["locked"][2];
  z4lock = doc["locked"][3];
  z5lock = doc["locked"][4];
  z6lock = doc["locked"][5];
  z7lock = doc["locked"][6];
  z8lock = doc["locked"][7];

}

