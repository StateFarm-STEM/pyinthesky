/*
  SD card datalogger

  This example shows how to log data from three analog sensors
  to an SD card using the SD library.

  The circuit:
   analog sensors on analog ins 0, 1, and 2
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created  24 Nov 2010
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>
#include "Adafruit_BMP085.h"
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

const int chipSelect = 10;

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;

// map sofware serial to gps
SoftwareSerial serialgps(TXPin, RXPin);

Adafruit_BMP085 bmp;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  delay(1000);


  Serial.print("initializing sd card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("failed");
    // don't do anything more:
    while (1);
  }
  Serial.println("initialized");

  initBMP();
  initGPS();
}



void loop() {
  
  // make a string for assembling the data to log:
  String dataString = "";
  bool gpsready = false;

  unsigned long start = millis();
  do
  {
    while (serialgps.available()>0) {
      char c;
      c=serialgps.read();
      gps.encode(c);
    }
  } while (millis() - start < 5000);


  float c = bmp.readTemperature();  // Variable for holding temp in C
  float f = c*1.8 + 32.;  // Variable for holding temp in F
  //float pressure = bmp.readPressure()/3386.3887; //pascals to in of mercury
  float p = bmp.readPressure(); //pascals
  
  dataString += String(c, 2);
  dataString += ",";
  dataString += String(f, 2);
  dataString += ",";
  dataString += String(p, 2);
  dataString += ",";
  
  if ((gps.location.age() < 1000 || gps.location.isUpdated()) && gps.location.isValid()) {
    if (gps.satellites.isValid() && (gps.satellites.value() > 3)) {
      dataString += (gps.course.isValid() ? (int)gps.course.deg() : 0);
      dataString += ",";
      dataString += (gps.speed.isValid() ? (int)gps.speed.knots() : 0);
      dataString += ",";
      dataString += (gps.location.isValid() ? (long)gps.altitude.feet() : 0);
      dataString += ",";
      dataString += (gps.hdop.isValid() ? (int)gps.hdop.value() : 0);
      dataString += ",";
      dataString += (gps.satellites.isValid() ? (int)gps.satellites.value() : 0);
      dataString += ",";
      dataString += (gps.location.isValid() ? (int)gps.location.age() : 0);
    
      float lat = gps.location.isValid() ? gps.location.lat() : 0;
      float lng = gps.location.isValid() ? gps.location.lng() : 0;
      
      dataString += ",";
      dataString += String(lat, 6);
      dataString += ",";
      dataString += String(lng, 6);
      dataString += ",";
      dataString += gps.charsProcessed();
      dataString += ",";
      dataString += gps.failedChecksum();
      dataString += ",";

      if (gps.date.isValid())
      {
        if (gps.date.month() < 10) dataString += String(F("0"));
        dataString += String(gps.date.month());
        dataString += String(F("/"));
        if (gps.date.day() < 10) dataString += String(F("0"));
        dataString += String(gps.date.day());
        dataString += String(F("/"));
        if (gps.date.year() < 10) dataString += String(F("0"));
        dataString += String(gps.date.year());
      }
      else
        dataString += "00/00/00";

      dataString += String(F(","));
  
      if (gps.time.isValid())
      {
        if (gps.time.hour() < 10) dataString += String(F("0"));
        dataString += String(gps.time.hour());
        dataString += String(F(":"));
        if (gps.time.minute() < 10) dataString += String(F("0"));
        dataString += String(gps.time.minute());
        dataString += String(F(":"));
        if (gps.time.second() < 10) dataString += String(F("0"));
        dataString += String(gps.time.second());
        dataString += String(F("."));
        dataString += String(gps.time.centisecond());
      }

      gpsready = true;
    }
  }

  if (gpsready) {
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
    // if the file is available, write to it:
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      // print to the serial port too:
      Serial.println(dataString);
    }
    // if the file isn't open, pop up an error:
    else {
      Serial.println("error opening datalog.txt");
    }
  }

  delay(2000);
}

void initGPS(){
  Serial.print("\ninitializing gps...");
  
  serialgps.begin(GPSBaud);
  delay(2000);
  if (!serialgps.available()) {
    Serial.println(F("initialization failed"));
    while (1);
  }
  else {
    Serial.println(F("initialized"));
  }
}

void initBMP(){
  Serial.print("\ninitializing bmp180...");

  unsigned status;
  
  status = bmp.begin();
  if (!status) {
    Serial.println(F("failed"));
  }
  else {
    Serial.println(F("initialized"));
  }
}
