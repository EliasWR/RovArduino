#include <Arduino.h>
#include "Functions.h"

void setMotorSpeeds(int zone, bool z1lock, bool z2lock, bool z3lock, 
bool z4lock, bool z5lock, bool z6lock, bool z7lock, bool z8lock) {

  switch (zone) {
  case 1: // North
    if (z1lock) {
      fullStop();
    } else {
      motor_1.writeMicroseconds(1600);    
      motor_2.writeMicroseconds(1500);
      motor_3.writeMicroseconds(1500);
    }
    break;
  case 2: // North-east
    if (z2lock) {
      fullStop();
    } else {
      motor_1.writeMicroseconds(1500);
      motor_2.writeMicroseconds(1600);
      motor_3.writeMicroseconds(1500);
    }
    break;
  case 3: // East
    if (z3lock) {
      fullStop();
    } else {
      motor_1.writeMicroseconds(1500);
      motor_2.writeMicroseconds(1500);
      motor_3.writeMicroseconds(1600);
    }
    break;
  case 4: // South-east
    if (z4lock) {
      fullStop();
    } else {
      motor_1.writeMicroseconds(1600);
      motor_2.writeMicroseconds(1500);
      motor_3.writeMicroseconds(1500);
    }
    break;
  case 5: // South
    if (z5lock) {
      fullStop();
    } else {
      motor_1.writeMicroseconds(1500);
      motor_2.writeMicroseconds(1600);
      motor_3.writeMicroseconds(1500);
    }
    break;
  case 6: // South-west
    if (z6lock) {
      fullStop();
    } else {
      motor_1.writeMicroseconds(1500);
      motor_2.writeMicroseconds(1500);
      motor_3.writeMicroseconds(1600);
    }
    break;
  case 7: // West
    if (z7lock) {
      fullStop();
    } else {
      motor_1.writeMicroseconds(1600);
      motor_2.writeMicroseconds(1500);
      motor_3.writeMicroseconds(1500);
    }
    break;
  case 8: // North-west
    if (z8lock) {
      fullStop();
    } else {
      motor_1.writeMicroseconds(1500);
      motor_2.writeMicroseconds(1600);
      motor_3.writeMicroseconds(1500);
    }
    break;
  case 9: // Clock wise
    motor_1.writeMicroseconds(1600);
    motor_2.writeMicroseconds(1600);
    motor_3.writeMicroseconds(1600);
    break;
  case 10:  // Counterclock wise
    motor_1.writeMicroseconds(1400);
    motor_2.writeMicroseconds(1400);
    motor_3.writeMicroseconds(1400);
  case -1:  // Stand still 
    fullStop();
    break;
  }
}

void setLights(int pwr) {
  int val;
  val = map(pwr, 0, 255, 1100, 1900); // 1900 draws 3A current
  port_light.writeMicroseconds(val);
  starboard_light.writeMicroseconds(val);
}

void fullStop() {
  motor_1.write(1500);
  motor_2.write(1500);
  motor_3.write(1500);
}