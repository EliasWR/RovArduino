#define Communication.h
#include "ArduinoJson.h"

extern StaticJsonDocument<48> doc;

void sendToRaspberry(int arg1, int arg2, bool arg3);