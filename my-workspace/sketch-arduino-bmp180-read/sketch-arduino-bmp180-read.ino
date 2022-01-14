
//#include <SD.h> // load the SD library
//#include <SPI.h> // load the SPI library

#include "Wire.h"    // imports the wire library for talking over I2C 
#include "Adafruit_BMP085.h"  // import the Pressure Sensor Library
Adafruit_BMP085 mySensor;  // create sensor object called mySensor

float tempC;  // Variable for holding temp in C
float tempF;  // Variable for holding temp in F
float pressure; //Variable for holding pressure reading

void setup(){
  Serial.begin(9600); //turn on serial monitor
  mySensor.begin();   //initialize mySensor
}



void loop() {
  tempC = mySensor.readTemperature(); //  Read Temperature
  tempF = tempC*1.8 + 32.; // Convert degrees C to F
  pressure=mySensor.readPressure(); //Read Pressure
  
  Serial.print("The Temp is: "); //Print Your results
  Serial.print(tempF);
  Serial.println(" degrees in F (fahrenheit)");
  Serial.print("The Pressure is: ");
  Serial.print(pressure/3386.389);
  Serial.println(" in of HG (inches of mercury).");
  Serial.println("");
  delay(250); //Pause between readings.
}
