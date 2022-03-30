#include <Arduino.h>  // Including the arduino functions (loop, setup)
#include <Servo.h>
#include <Wire.h>
#include "MS5837.h"
#include "TSYS01.h"
#include <ArduinoJson.h>

#include "Communication.h"
#include "Functions.h"


// Initialize objects
MS5837 pressSensor;
TSYS01 tempSensor;

byte pinM1 = 9;
byte pinM2 = 10;
byte pinM3 = 11;
byte l1 = 5;
byte l2 = 6;

//// Variable declaration
// Variables used locally in Arduino
int val;
int leakPin = 3;   // Leak Signal Pin //pin must be 3 not 1 or 2
int leak = 0;      // 0 = Dry , 1 = Leak  
float temp;
float pres;
bool leakStatus;
// Testing variables
String inputString = "";
bool stringComplete = false;

// "Second" initialization
Servo motor_1;
Servo motor_2;
Servo motor_3;
Servo starboard_light;
Servo port_light;

// Variables set by raspberry pi communication
int RP_led_sp;
int RP_mtr_dir;

StaticJsonDocument<48> outDoc;

void setup() {
  // Initialize serial communication with Raspberry PI
  Serial.begin(9600); 
  
  // Reserve byte for testing variable 
  inputString.reserve(200);


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
  // Lights are set to off
  motor_1.writeMicroseconds(1500);    
  motor_2.writeMicroseconds(1500);
  motor_3.writeMicroseconds(1500);
  // Serial.println("Initalizing motors");  // Will collide with JSON in python
  port_light.writeMicroseconds(1100);
  starboard_light.writeMicroseconds(1100);
  delay(7000);
}

void loop() {  
  // Read sensor values
  tempSensor.read();
  pressSensor.read();

  // Gets the sensor values and stores in local variable
  temp = tempSensor.temperature();
  pres = pressSensor.pressure();
  leakStatus = digitalRead(leakPin);

  
  // Serial with Raspberry Pi
  sendToRaspberry(temp, pres, leakStatus);
  receiveFromRaspberry();
  
  
}

