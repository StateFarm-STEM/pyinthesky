
//==========
// Libraries
//==========

// GPS libraries
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
//#include <Sodaq_DS3231.h>

// SD Card libraries
#include <SPI.h>
#include <SD.h>

// BMP180 libraries
#include "Wire.h"    // imports the wire library for talking over I2C 
#include "Adafruit_BMP085.h"  // import the fPrs Sensor Library

//=================
// Global variables
//=================

// Connect the RXD pin on the GPS to the Arduino digital 5 pin
// Connect the TXD pin oo the GPS to the Arduino digital 6 pin
// pass TXD pin number 6 as the first argument, followed by the RXD pin number 5
SoftwareSerial serialGPS(6, 5); // serial_conn
TinyGPSPlus gps;
Adafruit_BMP085 bmp180;  // create sensor object called bmp180
String sCSV = "";

//===================
// Main Code Sections
//===================

//void writeToFile(String fileName, String contentToWrite){
//    dataFile = SD.open(fileName, FILE_WRITE);
//    dataFile.println(contentToWrite);
//    dataFile.close();
//}

String getTime(){
  
  String timeString = "";
  
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) timeString += F("0");
    timeString += String(gps.time.hour()) + F(":");
    
    if (gps.time.minute() < 10) timeString += F("0");
    timeString += String(gps.time.minute()) + F(":");
    
    if (gps.time.second() < 10) timeString += F("0");
    timeString += String(gps.time.second());
//    timeString += String(gps.time.second()) + F(".");
    
//    timeString += String(gps.time.centisecond());
  }
  else
  {
    return F("INVALID");
  }

  return timeString;
}

// put your setup code here, to run once:
void setup() {

  // set the digital pin to the onboard LED:
  //pinMode(LED_BUILTIN, OUTPUT);

  // open serial port
  // over the USB cable
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  // open gps
  serialGPS.begin(9600);
  
  // open bmp180
  if (!bmp180.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while(1){}
  }
  
  // open sd card
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
}

// put your main code here, to run repeatedly:
void loop() {

  sCSV = "";

  // while there is information available to
  // read from the gps module
  //    read the data
  while(serialGPS.available()){
    gps.encode(serialGPS.read());
  }

  if(gps.location.isUpdated()){
    
    if (gps.location.isValid()){
    
      // read the values we are interested in and store in a variable

      // time info
      String sTime = getTime();
  
      // gps info
      String sSat = String(gps.satellites.value(), DEC);
      String sLat = String(gps.location.lat(),6);
      String sLng = String(gps.location.lng(),6);
      String sSpd = String(gps.speed.mph());
      String sAlt = String(gps.altitude.feet());

  
      // sensor info
      float fCel = bmp180.readTemperature(); //  Read degrees C
      float fFer = fCel*1.8 + 32.; // Convert degrees C to F
      String sCel = String(fCel, 6);
      String sFer = String(fFer, 6);
      // TODO: convert pressure
      String sPrs = String(bmp180.readPressure(), 6);
      
      // store the values we read above in a string using CSV format
      
      // time,sat,lat,lng,alt,spd,cel,fehr,press,hum
      // TODO: add humidity
      sCSV = sTime + "," + sSat + "," + sLat + "," + sLng + "," + sAlt + "," + sSpd + "," + sCel + "," + sFer + "," + sPrs;
//      Serial.println(sCSV);
    }
  }

  if(sCSV != ""){
    Serial.println(sCSV);
//    dataFile = SD.open("flight.log", FILE_WRITE);
//    dataFile.println(sCSV);
//    dataFile.close();
    delay(5000);
  }
}
