#include <SoftwareSerial.h>
#include <SPI.h> // communication
#include <MFRC522.h>
SoftwareSerial BlueSerial(8, 9); // RX, TX
char w;
boolean NL = true; //new line
MFRC522 mfrc522(10, 9);   // Create MFRC522 instance.
void setup() {
  Serial.begin(9600);
  BlueSerial.begin(9600);
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();

}

void loop() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

 if (BlueSerial.available()) {
   w = BlueSerial.read();
   Serial.write(w);

    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      BlueSerial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      BlueSerial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
     BlueSerial.println();
    BlueSerial.print("Message : ");
    content.toUpperCase();
    if (content.substring(1) == "BD 31 15 2B") //change here the UID of the card/cards that you want to give access
    {
      Serial.println("Authorized access");
      Serial.println();
      BlueSerial.println("Authorized access");
      BlueSerial.println();
      delay(3000);
    }

    else   {
      Serial.println(" Access denied");
      BlueSerial.println(" Access denied");
      delay(3000);
    }
  }
}

// if (BlueSerial.available()) {
//   w = BlueSerial.read();
//   Serial.write(w);
//   if (w == '1') {
//     Serial.println();
//     Serial.write("LED State Changed");
//     BlueSerial.write("LED State Changed");
//   }
// }
//
// if (Serial.available()) {
//   w = Serial.read();
//   BlueSerial.write(w);
//
//   if (NL) {
//     Serial.print(">");
//     NL = false;
//   }
//   Serial.write(w);
//   if (w == 10) {
//     NL = true;
//   }
//
