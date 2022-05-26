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

You must also make sure your device can connect to the internet, so there is a mac address script to upload to your ESP32 TTGO LoRa V1 board if you need to get its mac address.  When you run this script, be sure that you have the correct board selected in the Boards Manager in the Arduino IDE.  To do this, select Tools > Board > ESP32 Arduino > TTGO LoRa32-OLED V1.

Once you have the "one-click installer" downloaded, open it, select the port that your ESP32 TTGO LoRa V1 board is on (you can find this in the "Device Manager" application on your computer, under "Ports"), and then upload the code onto the ESP32 TTGO LoRa V1 board.  If you run into some issues with the code uploading to your board, run the "one-click installer" as an administrator on your computer.  Also, if you previously used the MAC Address script, make sure you have the serial monitor from the Arduino IDE closed when you do this step.

From here follow the instructions on the Quick-Start guide to setup your basestation. 

You're going to need to join the Telegram channel for TinyGS to get access to the TinyGS personal bot (join using this link: https://t.me/joinchat/DmYSElZahiJGwHX6jCzB3Q).  In the Telegram channel, you should be sent a welcome message that says you must open a private chat with the TinyGS personal bot to configure your ground station.  To do this, you must privately message @tinygs_personal_bot.  With this bot, type "/mqtt" into the private DM to get your MQTT username and password.  You put this username and password into your TinyGS basestation setup on the GUI ([see Quick-Start guide](https://github.com/G4lile0/tinyGS/wiki/Quick-Start)), specifically where it says "MQTT Username" and "MQTT password".  You can also DM the bot "/start" to obtain a welcome message and a list of other commands you can use with the bot.  (You can also join the other telegram channels TinyGS has by navigating to the "Community" section on this link: https://github.com/G4lile0/tinyGS)

Once your basestation parameters are filled out on the GUI ([see Quick-Start guide](https://github.com/G4lile0/tinyGS/wiki/Quick-Start)), click "Apply" and then your device should connect to your internet.  From here, type in the IP Address shown on the ESP32 TTGO LoRa V1 into your browser to get access to the basestation dashboard.  We will now switch over to useing the Adafruit Feather M0.

## Transmitting with the Adafruit Feather M0

Open the "adafruit_featherM0_RadioHeadTXCode" in Arduino IDE.  You will first need to go to "Manage Libraries" in Arduino and search "RadioLib".  Once this comes up, download it, then upload your code to the Adafruit Feather M0.  When the code is uploaded, pull up the Serial Monitor.  It should say packets are transmitting.  

## Next Steps

From here you should be able to see that your basestation GUI says that the ESP32 TTGO LoRa V1 board is receiving packets from the Adafruit Feather M0 through the terminal of your base station's dashboard. 

**NOTE: Make sure in "Configure Parameters" of the TinyGS Dashboard, the "Allow Automatic Tuning" box is UNCHECKED.

## Parameters

The following parameters should be the same (if possible) between the TinyGS basestation and the radio device that you are transmitting with:

    {"mode":"LoRa","freq":915.0,"bw":250.0,"sf":10,"cr":5,"sw":18,"pwr":5,"cl":120,"pl":8,"gain":0,"crc":true,"fldro":1,"sat":"Norbi","NORAD":46494}

To be clear, to change these parameters you must go to the home page of your dashboard, head to configuration, scroll all the way down to "Advanced Config", and edit the parameters in the "Modem startup" section.  Then, at the bottom, click "Apply" and return to your dashboard terminal.

## Forgotten Password/New WiFi Network Workarounds

If you have either forgotten your password to the dashboard or are on a new WiFi network, then you must do the following: Hit the reset button of your device and hold the program button for 10 seconds.  After this, the screen of the device will show its local IP address and from here you can connect to the device's dashboard (just like in the [Quick-Start guide](https://github.com/G4lile0/tinyGS/wiki/Quick-Start)), similar to how you connect when you first upload the code to the device via the "one-click installer".

### Past Issues 

* The packets are not readable on TinyGS --> FIXED - the CRC parameter on the TinyGS basestation must be set to "false" --> UPDATE: I fixed code on the the transmitter end to update the CRC value to "true".  Therefore, the TinyGS CRC parameter should be set to "true" now
* The TinyGS basestation that you setup will often switch over to listening to a different satellites parameters.  If this happens you must go to "Configure Parameters" and then click "Apply" again at the bottom.  This will reset the parameters, so that your basestation will keep listening to the Adafruit Feather M0. --> FIXED - On your TinyGS dashboard, in "Configure Parameters", make sure "Allow Automatic Tuning" is UNCHECKED

