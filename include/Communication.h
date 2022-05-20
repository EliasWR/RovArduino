#define Communication.h
#include "ArduinoJson.h"

// Defining global JSON documents
extern StaticJsonDocument<512> inDoc;   
extern StaticJsonDocument<48> outDoc;

// Functions declaration
void sendToRaspberry(float arg1, float arg2, bool arg3);
void receiveFromRaspberry();
