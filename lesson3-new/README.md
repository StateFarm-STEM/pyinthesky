# Welcome to lesson #3

## Getting started with Python on Arduino

### Objectives:
- Get aquanted with Python
- Intgrate Python with the Arduino
- Write your first Python code
- Make the onboard LED turn on and off

I found it easier to follow the guide and refer to the video when needed. The video only has music and plays very fast. You can slow this down if you like in YouTube under settings --> Playback speed.

![Settings --> Playback speed](https://github.com/StateFarm-STEM/pyinthesky/blob/main/lesson3-new/screenshots/yotube-settings-playback-speed.png)

Guide
[Using Arduino with Python – Controlling Arduino’s LED with Python](https://www.electronicshub.org/controlling-arduino-led-python/)

There are a few gotchas since Python language, runtime version, and pySerial version has changed since this video was published.

### Issues and fixes

Invalid syntax - ensure all the print statements use parenthesis<br>
ex. print (Arduino_Serial.readline())<br>
<br>
raw_input not defined - change raw_input to just input<br>
input_data = input()<br>
<br>
Unicode issue when pressing a number
Arduino_Serial.write(input_data.encode())

Video
[Using Arduino with Python – Controlling Arduino’s LED with Python](https://www.youtube.com/watch?v=4wWqka4EbEY)
