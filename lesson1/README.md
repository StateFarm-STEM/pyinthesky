# Lesson #1. Introduction and how to get started


## Objective:

- When flying high altitude balloon data is usually collected through the flight for later analysis. 
- The [National Weather Service](https://www.weather.gov/chs/upperair) launches a minimum of two high altitude balloons a day from [91 locations](https://www.weather.gov/upperair/nws_upper) every day at 1100 and 2300 UTC to observe weather conditions used to model weather forecasts.
- This project will launch their own weather balloon to the stratosphere or approximately 90,000+ feet.
  - Students will be responsible for tracking the following weather data:
    - Temperature around the balloon as it ascends 
    - Barometric pressure of the atmosphere at different altitudes 

  - Students will be recording the position of the balloon:
    - Latitude is recorded to map the flight path of the balloon
    - Longitude in conjunction with latitude we can plot the balloon’s location on a map 
    - Elevation is recorded for students to see how different factors can influence rate of ascent, peak elevation, etc. 
  - YOU will be [saving the data](https://create.arduino.cc/projecthub/electropeak/sd-card-module-with-arduino-how-to-read-write-data-37f390) in a [CSV file](https://en.wikipedia.org/wiki/Comma-separated_values) in a micro-SD card on the tracker in the following format every 30 seconds of the flight for later analysis:
    - time, latitude, longitude, altitude, temperature, humidity, pressure
  
- To build and test this you will be using:
  - ### [Arduino Uno](https://store.arduino.cc/products/arduino-uno-rev3)
  - This is a microcontroller. It is used to run code that stores data gathered from the onboard sensors.
    - ![Arduino UNO](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson1/arduino_uno.jpg)
  - ### [Breadboard](https://learn.sparkfun.com/tutorials/how-to-use-a-breadboard/all)
  -  This is used to prototype wiring and test to make sure things work before committing to soldering components together.
    - ![Breadboard](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson1/breadboard2.jpg)
  - ### [BMP-180 - Barometric Pressure/Temperature/Altitude Sensor](https://www.adafruit.com/product/1603)
  - This is used to get the barometric pressure, and temperature of the air surrounding it, as well as the altitude that the sensor is at. This data is recorded every 30 seconds to the micro-SD card
    - <img src="lesson1/photos/BMP both (2).jpg" width="100" >
  - ### [GPS Module](https://www.u-blox.com/en/product/neo-6-series)
  - This is how the balloon determines its latitude and longitude. The Arduino tells the GPS module to record its position every 30 seconds to the micro-SD card.
    - ![GPS NEO-6M](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson1/GPS_NEO-6M.JPG)
  - ### [Arduino SD card adapter](https://electropeak.com/micro-sd-tf-card-adapter-module)
  - This is how the micro-SD card is used by the Arduino to record data. It takes the data that the Arduino is giving it and writes it onto the micro-SD card.
    - ![SD Card Adapter](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson1/sd_card_module.jpg)
    
  - ### [Micro SD card](https://en.wikipedia.org/wiki/SD_card)
  - This stores all the data so you can access it later. 

Feel free to check out the links I have added in the [resource page](https://github.com/StateFarm-STEM/pyinthesky/blob/main/resources.md)
