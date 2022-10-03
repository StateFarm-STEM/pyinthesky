
## Putting it all together

You will now take everything you learned and apply them all into a single project that will take those measurements and GPS coordindates writing that information out to the Micro SD card using a data format called CSV (comma separated values).



#### Let's recap what you learned up to this point...

### Lesson 1

### key points
- you learned you will be writing code that will run on an Arduino that will fly to the stratosphere while taking measurements and gps coordinates along the way
- you learned you will save these individual measurements and coordinates in a file on the Micro SD card
- you learned this done every day across the US for modeling weather and predicting forecasts

### Lesson 2

#### key points
- you learned how to download, install, and create your first working Arduino Sketch
- you learned how to connect your Arduino Uno to your computer
- you learned how to turn on an off the light on the Arduino Uno
- you learned how to make your code sleep briefly between turning the light on and off


### Lesson 3

#### key points
- you learned how to use a bread board with your Arduino and the BMP180 sensor
- you learned how to import a library needed to talk to the BMP180
- you learned how to connect to the BMP sensor using a variable and take measurements
- you learned how to use variables to hold the individual measurements and write them out to  the serial port
- you learned how to view the measurements as your code ran on the Arduino using the Serial Port Monitor

### Lesson 4

#### key points
- you pretty much repeated the same things you learned in Lesson 4 as to how to connect to a module or sensor
- one exception is that you learned you needed a different library for the GPS module
- the other exception is that the code looked different, but similar too

### Lesson 5

#### key points
- you pretty much repeated the same things you learned in Lesson 4 and 5 as to how to connect to a module or sensor
- one exception is that you learned you needed a different library for the Micro SD card module
- the other exception is that you created a file on the card and wrote some data to the file



## HERE WE GO!

### Pre-requisites
- you should have a good grasp of using the breadboard to connect a module to the Arduino
- you should have a good grasp of what part of the code needed to match the pins for each module
- you should have completed all the lessons successfully
- you should have a conceptual idea of how each line in the code you have written relates to what is happening when it runs

### Objectives
- Learn how to wire the sensor and modules to the Arduino at the same time
  - we will have to change the pin numbers in the code to match the new pins you use for each module
- Learn what psuedo code is and write the pseudo code for the new program
- Learn just a little more about variables
  - name a variable (naming convention is an art form)
  - give a variable data to hang on to
  - data can be a reference to
    - an object like the GPS module, BMP180 sensor, or the Micro SD card
    - a piece of information like the temperature, altitude, date & time
  - format a string using variables (voila...CSV format)
- Learn just a little more about code structure - keep it simple!
  - readability, it should sorta read like an outline or a story (in my humble opinion) :)
  - reliability, it should always work and if it doesn't it should be able to recover
  - convert the pseudo code into code
- Learn how to debug your code when things aren't working as expected




### Working Code - Copy and paste this into your sketch 


``` 
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
```
