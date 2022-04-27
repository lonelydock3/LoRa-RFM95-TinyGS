//TX
// -*- mode: C++ -*-


#include <SPI.h>
#include <RadioLib.h>

#define RFM95_CS 8
#define RFM95_RST 9
#define RFM95_INT 3

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0
//#define RF95_FREQ 436.7

// Singleton instance of the radio driver
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
  // begin(freq, bw, sf, cr, syncWord, power, preambleLength, gain)
  int state = radio.begin(915.0, 250.0, 10, 5, 18, 5, 8, 0);
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  // saftey check to make sure frequency is at 915
  Serial.print(F("[RF95] Setting frequency ... "));
  state = radio.setFrequency(915.0);
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  // adjust output power, avialable ranges: -3 to 15 dBm
  // increasing power increases range of transmission
  Serial.print(F("[RF95] Setting Output Power parameter ... "));
  state = radio.setOutputPower(5); 
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("Output Power initialization error"));
    Serial.println(state);
    while (true);
  }

  // adjust spreading factor, avialable ranges: SF7 to SF12 (7 to 12)
  // increasing spreading factor increases range of transmission, but increases the time to transmit the message
  Serial.print(F("[RF95] Setting Spreading Factor parameter ... "));
  state = radio.setSpreadingFactor(10); 
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("Spreading Factor initialization error"));
    Serial.println(state);
    while (true);
  }

  // set CRC parameter to true so it matches the CRC parameter on the TinyGS side
  Serial.print(F("[RF95] Setting CRC parameter ... "));
  state = radio.setCRC(true, true); 
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("CRC initialization error"));
    Serial.println(state);
    while (true);
  }

  // set forceLDRO parameter to true so it matches the forceLDRO parameter on the TinyGS side
  Serial.print(F("[RF95] Setting forceLDRO parameter ... "));
  state = radio.forceLDRO(true); // FLDRO = 1 on TinyGS side
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("forceLDRO initialization error"));
    Serial.println(state);
    while (true);
  }

}

uint8_t byte_counter = 0x00;

void loop()
{
  // packet transmission
  Serial.print(F("[RF95] Transmitting packet ... "));
  // you can transmit C-string or Arduino string up to 64 characters long
  // int state = radio.transmit("Hello World!");

  // you can also transmit byte array up to 64 bytes long
  if (byte_counter == 20){
    byte_counter = 0x00;
  }
  byte byteArr[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, byte_counter};
  int state = radio.transmit(byteArr, 8);
  byte_counter ++;

  if (state == ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F("success!"));

  } else if (state == ERR_PACKET_TOO_LONG) {
    // the supplied packet was longer than 64 bytes
    Serial.println(F("too long!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);

  }

  // wait for a second before transmitting again
  delay(1000);
}
