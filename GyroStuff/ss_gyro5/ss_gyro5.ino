#include <SoftwareSerial.h>

#include <ADXL345.h>
#include <bma180.h>
#include <HMC58X3.h>
#include <ITG3200.h>
#include <MS561101BA.h>
#include <I2Cdev.h>
#include <MPU60X0.h>
#include <EEPROM.h>


//#define DEBUG
#include "DebugUtils.h"
#include "CommunicationUtils.h"
#include "FreeIMU.h"
#include <Wire.h>
#include <SPI.h>

float ypr[3]; // yaw pitch roll

// Set the FreeIMU object
FreeIMU my3IMU = FreeIMU();

SoftwareSerial mySerial(8, 9); // RX, TX

void setup() {
  Serial.begin(38400);
  Serial.println("rebooted");
  Wire.begin();
  mySerial.begin(38400);
  
  delay(5);
  my3IMU.init(); // the parameter enable or disable fast mode
  delay(5);
}

int iter=0;

void loop() { 
  iter++;
  handle_requests();
  
  my3IMU.getYawPitchRoll(ypr);
  if (iter%100==0) {  
    Serial.print("Yaw: ");
    Serial.print(ypr[0]);
    Serial.print(" Pitch: ");
    Serial.print(ypr[1]);
    Serial.print(" Roll: ");
    Serial.print(ypr[2]);
    Serial.println("");
  }
  
  delay(1);
}

void handle_requests() {
  while (mySerial.available()) {
    char c = mySerial.read();
    if (c=='f') {
      Serial.println("Got request!");
      mySerial.print("#YPR="); // That was litterly it
      mySerial.print(ypr[0]);
      mySerial.print(",");  
      mySerial.print(ypr[1]);
      mySerial.print(",");
      mySerial.println(ypr[2]);
      
    }
  }
}

