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

// Initializes run commands from the globals
int runZone = -1;   // Initial run state is set to offf
bool z1lock;
bool z2lock;
bool z3lock;
bool z4lock;
bool z5lock;
bool z6lock;
bool z7lock;
bool z8lock;

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

// Json document used to hold and format data to be sent to RPi
StaticJsonDocument<48> outDoc;

void setup() {
  // Initialize serial communication with RPi
  Serial.begin(9600); 

  // Initialize I2C bus sensors
  Wire.begin();
  pressSensor.init();
  tempSensor.init();

  // Declaring properties to pressure sensor object
  pressSensor.setModel(MS5837::MS5837_30BA);
  pressSensor.setFluidDensity(997);

  // Declaring PWM pins for motors and lights
  port_light.attach(l1);  
  starboard_light.attach(l2);
  motor_1.attach(pinM1);
  motor_2.attach(pinM2);  
  motor_3.attach(pinM3);

  // Declaring leak sensor as input
  pinMode(leakPin, INPUT);
  
  // Motors need to receive zero thrust signal for 7
  // seconds to properly initialize
  fullStop();
  setLights(0); // Lights are set to off for inital operation
  delay(7000);
}

void loop() {  
  // Read I2C sensor values
  tempSensor.read();
  pressSensor.read();

  // Gets the required sensor values and place in variables
  temp = tempSensor.temperature();
  depth = pressSensor.depth();
  leakStatus = digitalRead(leakPin);

  // Every 30 program iteration the Arduino sends data to Raspberry
  if (i > 30) {
    sendToRaspberry(temp, depth, leakStatus);
    i = 0;
  } 
  i++;

  // If data is found within serial buffer, handle data
  if (Serial.available()) {
    receiveFromRaspberry();
    missedPackets = 0;
  } else {  // Otherwise connection is broken and motors are stopped
    missedPackets++;
    if (missedPackets > 3) {
      fullStop();
    }
  }
  
  // Control motor speed and directions based on commanded zone
  // and information from collision avoidance system
  setMotorSpeeds(runZone, z1lock, z2lock, z3lock, 
  z4lock, z5lock, z6lock, z7lock, z8lock);
}

