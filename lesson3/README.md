
# Welcome to Lesson #3: Weather Sensor

## Working with weather sensor data using the Arduino language

#### Pre-requisites:
- you have successfully completed the [blinky lights lesson](https://github.com/StateFarm-STEM/pyinthesky/tree/main/lesson2#welcome-to-lesson-2)
- if not, do that first

#### Objectives:
- Breadboard a circuit
- Read weather sensor data
- Print the weather sensor data to the serial port

## Measure Pressure and Temperature using the BMP180

#### What you will be using:
- [Arduino IDE](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson4/screenshots/arduino-ide.png)
- [Arduino Uno](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson4/screenshots/arduino-uno-r3.png)
- [BMP180 Sensor](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson3/screenshots/bmp180.png)
- [5 pin connector](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson4/screenshots/5-pin-connector.png)
- [Breadboard](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson4/screenshots/breadboard.png)
- [Jumper Wires](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson3/screenshots/1956-02.jpg)

#### Note: the BMP180 Sensor didn't detect the pressure and temp accurately until I soldered the 5 pin connector to the BMP180<br>

#### What you will be learning:
- How to connect the BMP180 to the Arduino using a breadboard
- How to create a new Arduino Sketch project using the Adafruit BMP085 Library
- Write the code in the Arduino IDE and upload it to the Arduino
  - measure the temperature in Celsius from the BMP180 and convert to Fahrenheit
  - read the pressure in pascals and convert to inches of mercury
  - print your calculations to the Arduino's serial port
- Watch your code run on the Arduino using Arduino IDE's serial monitor

### Guide
[Python with Arduino LESSON 9 Measuring Pressure and Temperature with the BMP180 Sensor](https://toptechboy.com/python-with-arduino-lesson-9-measuring-pressure-and-temperature-with-the-bmp180-sensor/)

### Wiring diagram

Connecting Up the BMP180 Pressure and Temperature Sensor
| BMP180 Pin | Arduino Pin |
| -------------- | :--------- | 
Vin |	5V
GND	| GND
SCL	| A5
SDA	| A4
#### Helpful video shortcuts
- [connect the BMP180 to the Arduino](https://youtu.be/z9AzZM1-Dns?t=105)
- [how to add the Adafruit Library to the Arduino IDE](https://youtu.be/z9AzZM1-Dns?t=152)
- [write the code and run it on the Arduino](https://youtu.be/z9AzZM1-Dns?t=396)
- [convert pascals to inches of mercury](https://youtu.be/z9AzZM1-Dns?t=985)
### Tips
- the color of the wires do not matter as long as they are connected to the right pins
- make sure that you have the librarys installed [found here](https://learn.adafruit.com/bmp085/using-the-bmp085)



### Trouble shooting
- if you get an error code that looks like this `fatal error: Adafruit_I2CDevice.h` you are missing the BusIO library, follow [this guide](https://www.chippiko.com/ii2cdevice-no-such-file) to solve this issue
- After you run the code if you don't see data, make sure to open your serial monitor. ctrl + shift + m or enter the tools menu and select the serial monitor. 
- if you get in error like this one <code>Error opening serial port 'COM3'. (Port not found)
</code> while attempting to open your serial monitor, insure that your Arduino is still plugged in and everything is wired correctly

#### Working Code - if you get stuck click this link and copy and paste the code into your sketch
- [sketch-arduino-bmp180-read](https://github.com/StateFarm-STEM/pyinthesky/blob/main/my-workspace/sketch-arduino-bmp180-read/sketch-arduino-bmp180-read.ino)

### [Need help?](https://github.com/StateFarm-STEM/pyinthesky#need-some-help)
