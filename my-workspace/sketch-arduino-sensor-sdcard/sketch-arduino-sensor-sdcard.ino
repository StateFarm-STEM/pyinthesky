/*
  GPS Position Logger
  gps-position-logger.ino
  Read GPS data from BN-220 or any serial GPS sensor
  Requires TinyGPS++ Library
  Save to SD or microSD card

  bmp180 pins
  VIN - 5v
  GRD - gnd
  SCL - A5 analog
  SDA - A4 analog

  GPS pins
  TXD - 3 digital
  RXD - 4 digital
  GND - gnd
  VCC - 5v

  sdcard pins
  CS - 10 digital
  SCK - 13 digital
  MOSI - 11 digital
  MISO - 12 digital
  VCC - 5v
  GND - gnd

  DroneBot Workshop 2021
  https://dronebotworkshop.com/using-gps-modules/#Build_a_GPS_Position_Logger
*/

// Include required libraries
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include "Adafruit_BMP085.h"

// BMP sensor
Adafruit_BMP085 bmp180;
float tempC;  // Variable for holding temp in C
float tempF;  // Variable for holding temp in F
float pressure; //Variable for holding pressure reading

// GPS Connections
static const int RXPin = 4, TXPin = 3;

// GPS Baud rate (change if required)
static const uint32_t GPSBaud = 9600;

// SD Card Select pin
const int chipSelect = 10;

// Write LED
const int recLED = 7;

// String to hold GPS data
String gpstext;

// GPS write delay counter variables
// Change gpsttlcount as required
int gpscount = 0;
int gpsttlcount = 30;

// TinyGPS++ object
TinyGPSPlus gps;

// SoftwareSerial connection to the GPS device
SoftwareSerial ss(TXPin, RXPin);

void blinky()
{
  // Blink LED so we know we are ready
  digitalWrite(recLED, HIGH);
  delay(50);
  digitalWrite(recLED, LOW);
  delay(50);
  digitalWrite(recLED, HIGH);
  delay(50);
  digitalWrite(recLED, LOW);
  delay(50);
  digitalWrite(recLED, HIGH);
  delay(50);
  digitalWrite(recLED, LOW);
  
}

void setup()
{
  // Set LED pin as output
  pinMode(recLED, OUTPUT);

  pinMode(10, OUTPUT); // Add this line
  digitalWrite(10, HIGH); // Add this line  

  // Start Serial Monitor for debugging
  Serial.begin(115200);

  // Start SoftwareSerial
  ss.begin(GPSBaud);
  
  // Dispatch incoming characters
  while (ss.available() > 0)
  {
    gps.encode(ss.read());
    Serial.println("Encoding GPS data");
  }

  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    //don't do anything more:
    while (1);
  }
  Serial.println("Card initialized.");

  // not sure why, but this had to come 
  // after sd card for some reason
  bmp180.begin();
  
  // Blink LED so we know we are ready
  digitalWrite(recLED, HIGH);
  delay(50);
  digitalWrite(recLED, LOW);
  delay(50);
  digitalWrite(recLED, HIGH);
  delay(50);
  digitalWrite(recLED, LOW);
  delay(50);
  digitalWrite(recLED, HIGH);
  delay(50);
  digitalWrite(recLED, LOW);

}

void loop()
{

  // Turn off LED
  digitalWrite(recLED, LOW);

  // See if data available
  // NMEA data pulls down every 1 second
  while (ss.available() > 0)
    gps.encode(ss.read()); 
     
  //Serial.println("Reading GPS data");

  if (gps.location.isValid())
  {
    // See if we have a complete GPS data string
    if (getGPSInfo() != "0")
    {   
      // Get GPS string
      gpstext = getGPSInfo();

      if (gpscount == gpsttlcount) 
      {
        //Serial.println(F("Writing to SD Card..."));
        
        //Open the file on card for writing
        File dataFile = SD.open("gpslog.csv", FILE_WRITE);

        if (dataFile) 
        {
          // If the file is available, write to it and close the file
          dataFile.println(gpstext);
          dataFile.close();

          // Serial print GPS string for debugging
          Serial.println(gpstext);
          blinky();
        }
        // If the file isn't open print an error message for debugging
        else {
          Serial.println("error opening datalog.txt");
        }
      }
    } else {
      Serial.println("Error displaying location.");
    }
  }
  else
  {
    Serial.println("GPS location not valid.");
    //Serial.print("GPS serial overflow:");Serial.println(ss.overflow());  // For GPS serial troubleshooting
  }
  // Increment GPS Count
  gpscount = gpscount + 1;
  if (gpscount > gpsttlcount) {
    gpscount = 0;
  }
}

// Function to return GPS string
String getGPSInfo()
{
  // Define empty string to hold output
  String gpsdata = "";

  // Get latitude and longitude
  if (gps.location.isValid())
  {
    gpsdata = String(gps.location.lat(), 6);
    gpsdata += (",");
    gpsdata += String(gps.location.lng(), 6);
    gpsdata += (",");
  }
  else
  {
    return "0";
  }

  // Get Date
  if (gps.date.isValid())
  {
    gpsdata += String(gps.date.year());
    gpsdata += ("-");
    if (gps.date.month() < 10) gpsdata += ("0");
    gpsdata += String(gps.date.month());
    gpsdata += ("-");
    if (gps.date.day() < 10) gpsdata += ("0");
    gpsdata += String(gps.date.day());
  }
  else
  {
    return "0";
  }

  // Space between date and time
  gpsdata += (" ");

  // Get time
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) gpsdata += ("0");
    gpsdata += String(gps.time.hour());
    gpsdata += (":");
    if (gps.time.minute() < 10) gpsdata += ("0");
    gpsdata += String(gps.time.minute());
    gpsdata += (":");
    if (gps.time.second() < 10) gpsdata += ("0");
    gpsdata += String(gps.time.second());
  }
  else
  {
    return "0";
  }

  tempC = bmp180.readTemperature(); //  Read Temperature
  tempF = tempC*1.8 + 32.; // Convert degrees C to F
  pressure=bmp180.readPressure()/3386.389; //Read Pressure

  gpsdata += (",");
  gpsdata += String(tempC);
  gpsdata += (",");
  gpsdata += String(tempF);
  gpsdata += (",");
  gpsdata += String(pressure);


  // Return completed string
  return gpsdata;
}
