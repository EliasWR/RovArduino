#define Communication.h
#include "ArduinoJson.h"

extern StaticJsonDocument<512> inDoc;
extern StaticJsonDocument<48> outDoc;


// TESTING VARIABLE
extern char json[];

void sendToRaspberry(float arg1, int arg2, bool arg3);
void receiveFromRaspberry();