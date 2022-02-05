# LoRa-RFM95-TinyGS
Communicating from an Adafruit Feather M0 to TinyGS, using ESP32 TTGO LoRa V1 as a base station.

## ESP32 TTGO LoRa V1 Setup

Follow this guide to make sure your board is setup with the Arduino IDE: https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/

## Adafruit Feather M0 Setup

Follow this guide to make sure your board is setup with the Arduino IDE: https://learn.adafruit.com/adafruit-feather-m0-basic-proto/setup

Also follow this guide to install things in your board manager: https://learn.adafruit.com/adafruit-feather-m0-basic-proto/using-with-arduino-ide 

## TinyGS

You're going to want to take the ESP32 TTGO LoRa V1 board and plug it into your computer.  From there, go to this link: https://github.com/G4lile0/tinyGS/wiki/Quick-Start

Follow the steps to download the "one-click installer".

You must also make sure your device can connect to the internet, so there is a mac address script to upload to your ESP32 TTGO LoRa V1 board if you need to get its mac address.

Once you have the "one-click installer" downloaded, open it and then upload the code onto the ESP32 TTGO LoRa V1 board.

From here follow the instructions on the Quick-Start guide to setup your basestation. 

You're going to need to join the Telegram channel for TinyGS to get access to the TinyGS personal bot.  With this bot, you type "/mqtt" to get your MQTT username and password.  You put this username and password into your TinyGS basestation setup on the GUI, specifically where it says "MQTT Username" and "MQTT password".  (You can join the telegram channel, by navigating to the "Community" section on this link: https://github.com/G4lile0/tinyGS)

Once your basestation parameters are filled out on the GUI, click "Apply" and then your device should connect to your internet.  From here, type in the IP Address shown on the ESP32 TTGO LoRa V1 into your browser to get access to the basestation dashboard.  We will now switch over to useing the Adafruit Feather M0.

## Transmitting with the Adafruit Feather M0

Open the "adafruit_featherM0_RadioHeadTXCode" in Arduino IDE.  You will first need to go to "Manage Libraries" in Arduino and search "RadioLib".  Once this comes up, download it, then upload your code to the Adafruit Feather M0.  When the code is uploaded, pull up the Serial Monitor.  It should say packets are transmitting.  

## Next Steps

From here you should be able to see that your basestation GUI says that the ESP32 TTGO LoRa V1 board is receiving packets from the Adafruit Feather M0. 

**NOTE: Make sure in "Configure Parameters" of the TinyGS Dashboard, the "Allow Automatic Tuning" box is UNCHECKED.

## Parameters

The following parameters should be the same (if possible) between the TinyGS basestation and the radio device that you are transmitting with:

    {"mode":"LoRa","freq":915.0,"bw":250.0,"sf":10,"cr":5,"sw":18,"pwr":5,"cl":120,"pl":8,"gain":0,"crc":true,"fldro":2,"sat":"Norbi","NORAD":46494}

### Past Issues 

* The packets are not readable on TinyGS --> FIXED - the CRC parameter on the TinyGS basestation must be set to "false" --> UPDATE: I fixed code on the the transmitter end to update the CRC value to "true".  Therefore, the TinyGS CRC parameter should be set to "true" now
* The TinyGS basestation that you setup will often switch over to listening to a different satellites parameters.  If this happens you must go to "Configure Parameters" and then click "Apply" again at the bottom.  This will reset the parameters, so that your basestation will keep listening to the Adafruit Feather M0. --> FIXED - On your TinyGS dashboard, in "Configure Parameters", make sure "Allow Automatic Tuning" is UNCHECKED

