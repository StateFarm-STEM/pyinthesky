# Welcome to lesson 5 (not ready)

## Working with GPS sensor data using the Arduino language

#### Pre-requisites:
- you have successfully ran the blinky lights program on your Arduino
- if not, do that first

#### Objectives:
- Breadboard a circuit
- Read GPS sensor data
- Print the GPS sensor data to the serial port

## Measure Pressure and Temperature using the BMP180

#### What you will be using:
- [Arduino IDE](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson5/screenshots/arduino-ide.png)
- [Arduino Uno](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson5/screenshots/arduino-uno-r3.png)
- [GPS GT-U7 Sensor (GPS NEO 6M clone)](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson5/screenshots/gps-gt-u7.png)
- [5 pin connector](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson5/screenshots/5-pin-connector.png)
- [Breadboard](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson5/screenshots/breadboard.png)
- Wires

#### Note: the BMP180 Sensor didn't detect the pressure and temp accurately until I soldered the 5 pin connector to the BMP180<br>

#### What you will be learning:
- How to connect the GPS GT-U7 to the Arduino using a breadboard
- How to create a new Arduino Sketch project using the TinyGPS++ Library
- Write the code in the Arduino IDE and upload it to the Arduino
  - measure Latitude, Longitude, Altitude, speed, and the number of satellites you are connected to
  - read the pressure in pascals and convert to inches of mercury
  - print your calculations to the Arduino's serial port
- Watch your code run on the Arduino using Arduino IDE's serial monitor

### Video
[How to use the GT U7 GPS module](https://youtu.be/7zw2ULu73DY)

#### Helpful video shortcuts
- [connect the BMP180 to the Arduino](https://youtu.be/z9AzZM1-Dns?t=105)
- [how to add the TinyGPS++ Library to the Arduino IDE](https://youtu.be/z9AzZM1-Dns?t=152)
- [write the code and run it on the Arduino](https://youtu.be/7zw2ULu73DY?t=180)
- [convert pascals to inches of mercury](https://youtu.be/z9AzZM1-Dns?t=985)

#### Working project
- [sketch-arduino-gps-gt-u7-read](https://github.com/StateFarm-STEM/pyinthesky/tree/main/my-workspace/sketch-arduino-gps-gt-u7-read)
