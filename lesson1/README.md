# Lesson #1. Introduction and how to get started


## Objective:

- When flying  high altitude balloon data is usally collected through the flight for later analysis. 
- The [National Weather Service](https://www.weather.gov/chs/upperair) launches a minimum of two high altitude ballons a day from [91 locations](https://www.weather.gov/upperair/nws_upper) every day at 1100 and 2300 UTC to observe weather conditions used to model weather forcasts.
- This project will launch their own weather balloon to the stratosphere or approximately 90,000+ feet.
  - YOU will be responsible for tracking the following weather data:
    - Temperature
    - Humidity
    - Barometric pressure

  - YOU will be recording the position of the balloon:
    - Latitude
    - Longitude
    - Elevation
  - YOU will be [saving the data](https://create.arduino.cc/projecthub/electropeak/sd-card-module-with-arduino-how-to-read-write-data-37f390) in a [CSV file](https://en.wikipedia.org/wiki/Comma-separated_values) on the tracker in the following format every 30 seconds of the flight for later analysis:
    - time, latitude, longitude, altitude, temperature, humidity, pressure
- To build and test this you will be using:
  - [Arduino Uno](https://store.arduino.cc/products/arduino-uno-rev3)
  - [Breadboard](https://learn.sparkfun.com/tutorials/how-to-use-a-breadboard/all)
  - [BMP-180 - Barometric Pressure/Temperature/Altitude Sensor](https://www.adafruit.com/product/1603)
    - ![BMP-180 - Barometric Pressure/Temperature/Altitude Sensor](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson1/bmp180.JPG)
  - [GPS](https://www.u-blox.com/en/product/neo-6-series)
    - ![GPS NEO-6M](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson1/GPS_NEO-6M.JPG)
  - [Arduino SD card adapter](https://electropeak.com/micro-sd-tf-card-adapter-module)
    - ![SD Card Adapter](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson1/sd_card_module.jpg)
  - [Micro SD card](https://en.wikipedia.org/wiki/SD_card)
  - Extra temp probe jsut incase (DS18B20)
    - ![DS18B20](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson1/DS18B20.jpg)
