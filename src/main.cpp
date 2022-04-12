/**********************************************************************
 * PROGRAM THAT CONTROLS AN ARDUINO FOR A REMOTE OPERATING VEHICLE (ROV).
 * ROV IS DESIGNED FOR AQUACULTURE INSPECTION. THE PROGRAM CONTROLS 
 * MOVEMENT WITH THREE THRUSTERS AND VISION WITH TWO SUBSEA LIGHTS. 
 * ADDITIONALLY THE PROGRAM READS TEMPERATURE AND PRESSURE FROM THE
 * ENVIRONMENT THROUGH I2C COMMUNICATION. THE ARDUINO COMMUNICATES
 * WITH RASPBERRY PI THROUGH SERIAL COMMUNICATION.
 *********************************************************************/

#include <Arduino.h>  
#include <Servo.h>
#include <Wire.h>
#include "MS5837.h"
#include "TSYS01.h"
#include <ArduinoJson.h>
#include "Communication.h"
#include "Functions.h"


// Initialize I2C OBJECTS
MS5837 pressSensor;
TSYS01 tempSensor;

// Initialize actuator objects for motors and lights
Servo motor_1;
Servo motor_2;
Servo motor_3;
Servo starboard_light;
Servo port_light;

// Input and output pins are selected based on PWM capabilities
byte pinM1 = 9;
byte pinM2 = 10;
byte pinM3 = 11;
byte l1 = 5;
byte l2 = 6;

// Local variables used for logic and communication
int val;
int leakPin = 3;   // Leak Signal Pin //pin must be 3 not 1 or 2
int leak = 0;      // 0 = Dry , 1 = Leak  
float temp;
float depth;
bool leakStatus;
int missedPackets;
int i;

StaticJsonDocument<48> outDoc;

void setup() {
  // Initialize serial communication with Raspberry PI
  Serial.begin(9600); 

  // Initialize I2C bus
  Wire.begin();
  pressSensor.init();
  tempSensor.init();

  // Declaring properties to pressure sensor object
  pressSensor.setModel(MS5837::MS5837_30BA);
  pressSensor.setFluidDensity(997);

  // Declaring PWM pins for motors and lights
  port_light.attach(l1);  // switched from 5
  starboard_light.attach(l2);
  motor_1.attach(pinM1);
  motor_2.attach(pinM2);  // switched from 10
  motor_3.attach(pinM3);
  pinMode(leakPin, INPUT);
  
  // Motors need to receive zero thrust signal for some time
  // before receiving additional commands 
  fullStop();
  setLights(0); // Lights are set to off for inital state
  delay(7000);
}

void loop() {  
  // Read sensor values
  tempSensor.read();
  pressSensor.read();

  // Gets the sensor values and stores in local variable
  temp = tempSensor.temperature();
  depth = pressSensor.depth();
  leakStatus = digitalRead(leakPin);

  // Every 30 program iteration the Arduino sends data to Raspberry
  if (i > 30) {
    sendToRaspberry(temp, depth, leakStatus);
    i = 0;
  }

  i++;

  if (Serial.available()) {
    receiveFromRaspberry();
    missedPackets = 0;
  } else {
    missedPackets++;
    if (missedPackets > 3) {
      fullStop();
    }
  }
  

  /* 
  // This solution for serial communication sends less packets, and is 
  // a bit more reliable, however does not notice when serial communication
  // is offline.
  sendToRaspberry(temp, pres, leakStatus);
  receiveFromRaspberry();
  */
  
}

