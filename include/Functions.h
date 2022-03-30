#define Functions.h
#include "Servo.h"

// Declaring three global servo objects
extern Servo motor_1;
extern Servo motor_2;
extern Servo motor_3;
extern Servo starboard_light;
extern Servo port_light;

void setMotorSpeeds(int zone, bool z1lock, bool z2lock, bool z3lock, 
bool z4lock, bool z5lock, bool z6lock, bool z7lock, bool z8lock);

void setLights(int pwr);
void fullStop();