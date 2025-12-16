Noise Pollution Montitor:

The purpose of this project was to allow the user to obtain data on the sound levels that a microphone, being used by an ESP32, would pick up.

Parts Used:
- ESP32 DevKit V1
- KeyeStudio KS0035 Analog Sound Monitor

How to Connect the Parts:
- Connect the V pin on the Sound Monitor to the 3V3 pin on the ESP32.
- Connect The G pin on the Sound Monitor to the GND pin on the ESP32.
- Connect the S pin on the Sound Monitor to the D33 pin on the ESP32.

How to use:
- In the same file, make sure that _SoundMonitor.h_, _SoundMonitor.cpp_, and _main.ino_ are in the same folder. You can also include _NoiseMonitor_UI.html_ for simplicity.
- After connecting the parts, in _main.ino_, set the SSID and the Password to the WiFi name and password that you want the ESP32 to connect to.
- Make sure that both you computer and ESP32 are on the same network.
- Upload the code to the ESP32.
- In the serial terminal in the Arduino IDE, grab the IP address of the ESP32 after successfully connecting to the WiFi.
- After obtaining the IP address for the ESP32, under _update()_ in _NoiseMonitor_UI.html_, replace "Your ESP32 IP address" in "fetch('http://Your ESP32 IP Address/sound');".
- After doing so, save the file.
- Ensure that the ESP32 is running and then open up the webpage.

Troubleshooting:
- During the process, we often found that the sound sensor would have a lot connectivity issues. One workaround found was to blow directly into the microphone until noise was picked up.
- If you find that the ESP32 struggles to connect to the WiFi, click the EN button on the ESP32 to reset it and have it attempt the connection again.
- If you find the webpage rapidly say connection error, either ensure that you have a stable connection or refresh the webpage. 
