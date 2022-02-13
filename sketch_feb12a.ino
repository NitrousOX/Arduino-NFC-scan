#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         5
#define SS_PIN          10

String MasterTag = "D2D5F71B";
String TagId;
byte readCard[4];


MFRC522 RFIDReader(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  while(!Serial);
  SPI.begin();
  RFIDReader.PCD_Init();
  delay(4);
}

void loop(){
  
  while(getID())
      if(TagId == MasterTag)
        Serial.println('1');
      else
        Serial.println('0');
}

boolean getID(){
  if(!RFIDReader.PICC_IsNewCardPresent())
    return false;
  if(!RFIDReader.PICC_ReadCardSerial())
    return false;
  TagId = "";

  for(uint8_t i=0;i<4;i++)
    TagId.concat(String(RFIDReader.uid.uidByte[i],HEX));
  TagId.toUpperCase();
  RFIDReader.PICC_HaltA();
  
  return true;
}
