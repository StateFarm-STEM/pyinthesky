
#include <Timezone.h>   // https://github.com/JChristensen/Timezone

// SD card include libraries
//--------------------------

#include <SD.h> // load the SD library
#include <SPI.h> // load the SPI library

// SD card include libraries
//--------------------------

#include "Wire.h"    // imports the wire library for talking over I2C 
#include "Adafruit_BMP085.h"  // import the Pressure Sensor Library

// sensor variables
//-----------------

Adafruit_BMP085 mySensor;  // create sensor object called mySensor

float tempC;  // Variable for holding temp in C
float tempF;  // Variable for holding temp in F
float pressure; //Variable for holding pressure reading

// sdcard variables
//-----------------

File myFile;
int digitalPin=4; // this number needs to match the digital pin number CS is connected to

void setup(){

  // initialize the serial monitor
  //------------------------------
  
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
  
    // initialize the SD card
    //-----------------------
  
    Serial.print("Initializing SD card...");
    
    if (!SD.begin(4)) {
      Serial.println("initialization failed!");
      while (1); // why are we doing this? can we just exit?
    }
    
    Serial.println("SD card initialization done.");

  // create a test file
  //-------------------

    Serial.println("Creating data file...");
    
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    myFile = SD.open("datafile.log", FILE_WRITE);
    
    if (myFile) {
      Serial.println("data file created.");
      myFile.close();
    }
    else {
      Serial.println("error opening data file.");
      while(1);
    }
    
    Serial.println("Initializing the sensor...");
    
  // initialize the sensor
  //----------------------

    Serial.println("Initializing the sensor...");
    
    mySensor.begin();   //initialize mySensor

    Serial.println("setup complete.");
    
    
}



void loop() {

  // take sensor readings
  //---------------------

  time_t utc = now();
  
  tempC = mySensor.readTemperature(); //  Read Temperature
  tempF = tempC*1.8 + 32.; // Convert degrees C to F
  pressure=mySensor.readPressure(); //Read Pressure

  // print results to the serial port
  //---------------------------------

  Serial.print("The time in UTC is: ");
  Serial.println(utc);
  Serial.print("The Temp is: "); //Print Your results
  Serial.print(tempF);
  Serial.println(" degrees F");
  Serial.print("The Pressure is: ");
  Serial.print(pressure);
  Serial.println(" Pa.");
  Serial.println("");
  
  // write data to data file
  //------------------------
  
  myFile = SD.open("datafile.log", FILE_WRITE);

  if (myFile) {
    myFile.print("TODO");
    myFile.print(",");
    myFile.print(tempC);
    myFile.print(",");
    myFile.print(tempF);
    myFile.print(",");
    myFile.println(pressure);
    myFile.close();
  }
  else {
    Serial.println("error opening data file.");
  }
  
  
  delay(250); //Pause between readings.
}
