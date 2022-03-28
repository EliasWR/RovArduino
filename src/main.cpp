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

char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";


void setup() {
  // Initialize serial communication with Raspberry PI
       
  
  
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
  // Serial.println("Initalizing motors");
  port_light.writeMicroseconds(1100);
  starboard_light.writeMicroseconds(1100);
  delay(7000);


  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(38400); 

  
}

void loop() {  
  // Read sensor values
  tempSensor.read();
  pressSensor.read();

  RP_led_sp = 120;  // Testing value, this is originally sent from RP
  val = map(RP_led_sp, 0, 255, 1100, 1900);

  // Gets the sensor values and stores in local variable
  temp = tempSensor.temperature();
  pres = pressSensor.pressure();
  leakStatus = digitalRead(leakPin);

  //sendToRaspberry(temp, pres, leakStatus);
  // Can introduce if statement if only sending data when new readning
  // if (Serial.available() > 0) { // Checks if number of bytes in input buffer is over 0
  // }
  


  

  // If there is data to be received, deserialize the JSON into global variables
  /*
  if (Serial.available() > 0 or true) { 
    receiveFromRaspberry();   
  }
  */

  
  
  // sendToRaspberry(temp, pres, leakStatus);

  //delay(20);
  
  sendToRaspberry(temp, pres, leakStatus);

  
  
  if ( Serial.available() ) {
    //setMotorSpeeds(0);
    receiveFromRaspberry();
    /*
    String  payload;
    payload = Serial.readStringUntil( '\n' );
    StaticJsonDocument<512> doc;
    deserializeJson(doc, payload);
    if (doc["operation"] == "sequence") {
      setMotorSpeeds(0);
      
    }
    else {
      //setMotorSpeeds(0);
    }
    */
  }
  

  //DeserializationError error = deserializeJson(doc, payload);
  //if (error) {
  //  Serial.println(error.c_str()); 
  //  return;
  
  
    
    
    
    //
  
  
  

  /*
  setMotorSpeeds(0);
  Serial.println(motor_1.readMicroseconds());
  delay(5000);
  setMotorSpeeds(1);
  Serial.println(motor_1.readMicroseconds());
  delay(5000);
  setMotorSpeeds(2);
  delay(5000);
  setMotorSpeeds(3);
  delay(5000);
  */
  
  
  

  port_light.writeMicroseconds(val);
  starboard_light.writeMicroseconds(val);

}