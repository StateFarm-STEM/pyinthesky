# Welcome to Lesson #4: GPS Sensor

## Working with GPS sensor data using the Arduino language

#### Pre-requisites:
- you have successfully completed the [blinky lights lesson](https://github.com/StateFarm-STEM/pyinthesky/tree/main/lesson2#welcome-to-lesson-2)
- if not, do that first

#### Objectives:
- Breadboard a circuit
- Read GPS sensor data
- Print the GPS sensor data to the serial port
- Monitor data on the serial monitor

## Read GPS location data using the GPS GT-U7 Module

#### What you will be using:
- [Arduino IDE](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson5/screenshots/arduino-ide.png)
- [Arduino Uno](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson5/screenshots/arduino-uno-r3.png)
- [GPS GT-U7 Sensor (GPS NEO 6M clone)](https://github.com/StateFarm-STEM/pyinthesky/blob/lesson-3-continued/lesson4/screenshots/gps-gt-u7.png)
- [5 pin connector](https://raw.githubusercontent.com/StateFarm-STEM/pyinthesky/lesson-3-continued/lesson4/screenshots/2076789.webp)
- [Breadboard](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson5/screenshots/breadboard.png)
- Wires

#### Note: I had some issues using the GPS module from inside my garage. Here are some things you can try to get good results...<br>
- try working near a window with the best view of the sky
- try taking your laptop outside
- if it works where you like to work, then great

#### What you will be learning:
- How to connect the GPS GT-U7 to the Arduino without using a breadboard (changes it up just a little here compared to lesson 3)
- How to create a new Arduino Sketch project using the TinyGPSPlus Library
- Write the code in the Arduino IDE and upload it to the Arduino
  - read Latitude, Longitude, Altitude, speed, and the number of satellites you are connected to from the GPS module
  - print your results to the Arduino's serial port
- Watch your code run on the Arduino using Arduino IDE's serial monitor

### Video
[How to use the GT U7 GPS module](https://youtu.be/7zw2ULu73DY)

#### How to get the TinyGPSPlus library:

Right-click the following two links and choose "save link as" saving them to the same location as your Sketch project file
- [TinyGPSPlus.cpp](https://github.com/StateFarm-STEM/pyinthesky/blob/main/my-workspace/sketch-arduino-gps-gt-u7-read/TinyGPSPlus.cpp)
- [TinyGPSPlus.h](https://github.com/StateFarm-STEM/pyinthesky/blob/main/my-workspace/sketch-arduino-gps-gt-u7-read/TinyGPSPlus.h)

#### Helpful video shortcuts
- [connect the GPS GT-U7 to the Arduino](https://youtu.be/7zw2ULu73DY?t=54)
- [write the code and run it on the Arduino](https://youtu.be/7zw2ULu73DY?t=180)
#### Tips
- make sure that your wires are in the correct pins. The pin labeled TXD should be routed to pin 10 on the Arduino. RXD on the GPS to pin 11. GND on the GPS should be to GND on the Arduino, VDC to 5 volts.
#### Working project
- [sketch-arduino-gps-gt-u7-read](https://github.com/StateFarm-STEM/pyinthesky/tree/main/my-workspace/sketch-arduino-gps-gt-u7-read)

### [Need help?](https://github.com/StateFarm-STEM/pyinthesky#need-some-help)

