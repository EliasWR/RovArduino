/**********************************************************************
 * SUBPROGRAM OF THE ARDUINO UNO CODE FOR CONTROLLING ROV. FILE CONTAINS
 * THE FUNCTIONS NEEDED TO CONTROL THE MOTORS AND LIGHTS.
 *********************************************************************/
#include <Arduino.h>
#include "Functions.h"

/**
 * Function that controls the direction the ROV is moving in. Takes in 
 * a zone that operator wants the ROV to be moving towards, and given that
 * zone is not prohibited from the interlocking system, the function sends out
 * the appropiate PWM signals to the motor drivers. In addition to linear 
 * movements, the ROV can rotate both clockwise -and counterclockwise, these
 * directions are never prohibited by the interlocing system.
 * @param zone    Requsted propulsion in this zone direction
 * @param z1lock  Propulsion in zone 1 direction prohibited variable
 * @param z2lock  Propulsion in zone 2 direction prohibited variable
 * @param z3lock  Propulsion in zone 3 direction prohibited variable
 * @param z4lock  Propulsion in zone 4 direction prohibited variable
 * @param z5lock  Propulsion in zone 5 direction prohibited variable
 * @param z6lock  Propulsion in zone 6 direction prohibited variable
 * @param z7lock  Propulsion in zone 7 direction prohibited variable
 * @param z8lock  Propulsion in zone 8 direction prohibited variable
 */

void setMotorSpeeds(int zone, bool z1lock, bool z2lock, bool z3lock, 
bool z4lock, bool z5lock, bool z6lock, bool z7lock, bool z8lock) {
  switch (zone) {
  case 0: // Forward
    if (z1lock) {
      fullStop();
    } else {
      controlMovement(1550, 1550, 1500);
    }
    break;
  case 1: // Forward-right
    if (z2lock) {
      fullStop();
    } else {
      controlMovement(1550, 1500, 1550);
    }
    break;
  case 2: // Right
    if (z3lock) {
      fullStop();
    } else {
      controlMovement(1530, 1470, 1550);
    }
    break;
  case 3: // Reverse-right
    if (z4lock) {
      fullStop();
    } else {
      controlMovement(1500, 1450, 1550);
    }
    break;
  case 4: // Reverse
    if (z5lock) {
      fullStop();
    } else {
      controlMovement(1450, 1450, 1500);
    }
    break;
  case 5: // Reverse-left
    if (z6lock) {
      fullStop();
    } else {
      controlMovement(1450, 1500, 1450);
    }
    break;
  case 6: // Left
    if (z7lock) {
      fullStop();
    } else {
      controlMovement(1470, 1530, 1450);
    }
    break;
  case 7: // Forward-left
    if (z8lock) {
      fullStop();
    } else {
      controlMovement(1500, 1550, 1450);
    }
    break;
  case 8: // Counterclock-wise
    controlMovement(1470, 1530, 1530);
    break;
  case 9:  // Clock-wise
    controlMovement(1530, 1470, 1470);
    break;
  case -1:  // Stand still 
    fullStop();
    break;
  }
}

/**
 * Sets subsea lights power output, both lights have the exact same value. Takes
 * in an integer that ranges from 0-255 and translates that to 0-100% light power.
 * Sets light with PWM setting.
 * @param pwr      Integer that ranges from 0-255 for 0-100% power
 */
void setLights(int pwr) {
  int val;
  val = map(pwr, 0, 255, 1100, 1500); // 1900 draws 2.5A current
  port_light.writeMicroseconds(val);
  starboard_light.writeMicroseconds(val);
}

/**
 * Function that sets all motors to neutral output. Zero propulsion in any
 * direction for all three motors.
 */
void fullStop() {
  motor_1.write(1500);
  motor_2.write(1500);
  motor_3.write(1500);
}

/**
 * Function that sets all the motor power and direction outputs. Takes in three
 * arguments with PWM settings that controls each respective motor.
 * @param m1pwr      PWM setting for motor 1
 * @param m2pwr      PWM setting for motor 2
 * @param m3pwr      PWM setting for motor 3
 */
void controlMovement(int m1pwr, int m2pwr, int m3pwr) {
  motor_1.writeMicroseconds(m1pwr);
  motor_2.writeMicroseconds(m2pwr);
  motor_3.writeMicroseconds(m3pwr);
}

/**
 * Function that rounds an input float number to a new float number with reduced
 * number of decimals.
 * @param value      input argument for number to reduce decimals
 * @param prec       number of decimals to be returned
 * @return           returns a float number rounded as specificed
 */
float roundNum(float value, unsigned char prec) {
  float pow_10 = pow(10.0f, (float)prec);
  return round(value * pow_10) / pow_10;
}