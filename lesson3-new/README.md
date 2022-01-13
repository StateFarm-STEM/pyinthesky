## New Instructions

### since the above links use components that aren't in the kit we are using I found a lesson that blinks the onboard led

This first step will get all the setup out of the way to use get Python and the pySerial library installed. Pythong is the coding language and pySerial is needed so the code can talk to the Arduino over USB.

I found it easier to follow the guide and refer to the video when needed. The video only has music and is very fast. You can slow this down if you like.

Guide
[Using Arduino with Python – Controlling Arduino’s LED with Python](https://www.electronicshub.org/controlling-arduino-led-python/){:target="_blank"}

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
[Using Arduino with Python – Controlling Arduino’s LED with Python](https://www.youtube.com/watch?v=4wWqka4EbEY){:target="_blank"}
