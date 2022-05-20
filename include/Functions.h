#define Functions.h
#include "Servo.h"

// Declaring global servo objects
extern Servo motor_1;
extern Servo motor_2;
extern Servo motor_3;
extern Servo starboard_light;
extern Servo port_light;

// Declaring global variables
extern int runZone;
extern bool z1lock;
extern bool z2lock;
extern bool z3lock;
extern bool z4lock;
extern bool z5lock;
extern bool z6lock;
extern bool z7lock;
extern bool z8lock;

// Functions declaration
void setMotorSpeeds(int zone, bool z1lock, bool z2lock, bool z3lock, 
bool z4lock, bool z5lock, bool z6lock, bool z7lock, bool z8lock);
void setLights(int pwr);
void fullStop();
void controlMovement(int m1pwr, int m2pwr, int m3pwr);
float roundNum(float value, unsigned char prec);