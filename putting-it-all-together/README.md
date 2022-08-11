
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
- you learned how to use variables to hold the individual measurements and write them out to the serial port
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

### Extra Credit
- functions, they help with readability and repeatable tasks


