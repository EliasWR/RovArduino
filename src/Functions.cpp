#include <Arduino.h>
#include "Functions.h"

void setMotorSpeeds (int zone) {
  switch (zone) {
  case 0: // Current with lights 12V: 680mA
    motor_1.writeMicroseconds(1600);    
    motor_2.writeMicroseconds(1600);
    motor_3.writeMicroseconds(1600);
    break;
  case 1: // Current with lights 12V: 
    motor_1.writeMicroseconds(1700);
    motor_2.writeMicroseconds(1700);
    motor_3.writeMicroseconds(1700);
    break;
  case 2:
    motor_1.writeMicroseconds(1800);
    motor_2.writeMicroseconds(1800);
    motor_3.writeMicroseconds(1800);
    break;
  case 3:
    motor_1.writeMicroseconds(1900);
    motor_2.writeMicroseconds(1900);
    motor_3.writeMicroseconds(1900);
    break;
  case 4:
    motor_1.writeMicroseconds(2000);
    motor_2.writeMicroseconds(2000);
    motor_3.writeMicroseconds(2000);
    break;
  case 5:
    motor_1.write(3);
    motor_2.write(3);
    motor_3.write(3);
    break;
  case 6:
    motor_1.write(3);
    motor_2.write(3);
    motor_3.write(3);
    break;
  case 7:
    motor_1.write(3);
    motor_2.write(3);
    motor_3.write(3);
    break;
  case 8:
    motor_1.write(3);
    motor_2.write(3);
    motor_3.write(3);
    break;
  case 9:
    motor_1.write(3);
    motor_2.write(3);
    motor_3.write(3);
    break;
  }
}