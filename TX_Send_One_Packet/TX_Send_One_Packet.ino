//TX
// -*- mode: C++ -*-
//On RESET, send one packet


#include <SPI.h>
#include <RadioLib.h>

#define RFM95_CS 8
#define RFM95_RST 9
#define RFM95_INT 3

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0
//#define RF95_FREQ 436.7

// Singleton instance of the radio driver
//RF95 rf95 = new Module(RFM95_CS, RFM95_INT);
RFM95 radio = new Module(RFM95_CS, RFM95_INT, RFM95_RST);
void setup() 
{
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  //while (!Serial);
  Serial.begin(9600);
  delay(100);

  Serial.println("Arduino LoRa TX Test!");

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  Serial.print(F("[RF95] Initializing ... "));
//  int state = radio.begin(915.0, 250.0, 10, 5);
  int state = radio.begin(915.0, 250.0, 10, 5, 18, 5, 8, 0);
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  Serial.print(F("[RF95] Setting frequency ... "));
    state = radio.setFrequency(915.0);
    if (state == ERR_NONE) {
      Serial.println(F("success!"));
    } else {
      Serial.print(F("failed, code "));
      Serial.println(state);
      while (true);
    }

    Serial.print(F("[RF95] Transmitting packet ... "));

    state = radio.setCRC(true, true); 
    if (state == ERR_NONE) {
      Serial.println(F("success!"));
    } else {
      Serial.print(F("CRC initialization error"));
      Serial.println(state);
      while (true);
    }

  // you can transmit C-string or Arduino string up to 64 characters long
  int state2 = radio.transmit("Hello World!");

  // testing with CRC value
//  int state2 = radio.transmit("A");

  // you can also transmit byte array up to 64 bytes long
  
//  byte byteArr[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
//  int state2 = radio.transmit(byteArr, 8);

  if (state2 == ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F("success!"));

  } else if (state2 == ERR_PACKET_TOO_LONG) {
    // the supplied packet was longer than 64 bytes
    Serial.println(F("too long!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state2);

  }

}

void loop()
{
  

  // wait for a second before transmitting again
  delay(1000);
}
