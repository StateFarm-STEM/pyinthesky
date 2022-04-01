
//==========
// Libraries
//==========

// GPS libraries
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

// SD Card libraries
#include <SPI.h>
#include <SD.h>

// BMP180 libraries
#include "Wire.h"    // imports the wire library for talking over I2C 
#include "Adafruit_BMP085.h"  // import the Pressure Sensor Library

//=================
// Global variables
//=================

// Create the serial_connection
//
// Connect the GT-U7 GPS Module RX and TX pins to the Arduino
// digital pins on the board.
//
// Connect the RXD pin on the GPS to the Arduino digital 5 pin
// Connect the TXD pin oo the GPS to the Arduino digital 6 pin
//
// pass TXD pin number 6 as the first argument, followed by the RXD pin number 5
//
SoftwareSerial serialGPS(6, 5); // serial_conn
TinyGPSPlus gps;
File dataFile;
Adafruit_BMP085 mySensor;  // create sensor object called mySensor

//===================
// Main Code Sections
//===================

// put your setup code here, to run once:
void setup() {

  // open serial port
  // over the USB cable
  Serial.begin(9600);
  // open gps
  serialGPS.begin(9600);
  // open sd card
  SD.begin(10);
}

// put your main code here, to run repeatedly:
void loop() {

  //Serial.println("a");

  // while there is information available to
  // read from the gps module
  //    read the data
  while(serialGPS.available())
  {
    //Serial.println("b");
    gps.encode(serialGPS.read());
  }

  //Serial.println("c");

  // any time the gps location changes
  // read all the individual value we are interested in
  // format the string using CSV format
  //
  // cvs format is a string containing different values separated by a comma...
  // value1,value2,value3,...
  //
  if(gps.location.isUpdated())
  {
    Serial.println("d");
    
    // read the values we are interested in and store in a variable
    Serial.println("gps updated");

    // gps info
    int numberOfSatellites = gps.satellites.value();
    float latitude = gps.location.lat();
    float longitude = gps.location.lng();
    float speedInMph = gps.speed.mph();
    float altitudeInFeet = gps.altitude.feet();

    // sensor info
    float tempC = mySensor.readTemperature(); //  Read degrees C
    float tempF = tempC*1.8 + 32.; // Convert degrees C to F
    float pressure=mySensor.readPressure(); //Read Pressure

    // store the values we read above in a string using CSV format
    
    // numberOfSatellites,latitude,longitude,speedInMph,altitudeInFeet,tempC,tempF,pressure
    String csvString = String(numberOfSatellites, DEC) + "," + String(latitude, 12) + "," + String(longitude, 12) + "," + String(speedInMph, 4) + "," + String(altitudeInFeet, 6) + "," + tempC + "," + tempF + "," + pressure;
    Serial.println(csvString);
    
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    dataFile = SD.open("flight.log", FILE_WRITE);
    dataFile.println(csvString);
  
    // always close the file when done
    dataFile.close();

    delay(1000);
  }
}
