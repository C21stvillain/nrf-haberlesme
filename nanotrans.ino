#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(10, 9); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

struct Data_Package {
  byte a = 0;
  byte b = 2;
  byte c = 55;
  int d = 124;
  float e = 32.141592;
  String f = "alici verici";
};

struct Data2_Package {
  byte a = 1;
  byte b = 3;
  byte c = 45;
  int d = 127;
  float e = 34.123;
  String f = "Verici alici";
};

Data2_Package data2;
Data_Package data;

void setup() {
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  delay(5);

  radio.stopListening();
  radio.write(&data, sizeof(Data_Package));

  delay(5);
  radio.startListening();
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure
    Serial.print("a: ");
    Serial.print(data.a);
    Serial.print(" b: ");
    Serial.print(data.b);
    Serial.print(" c: ");
    Serial.print(data.c);
    Serial.print(" d: ");
    Serial.print(data.d);
    Serial.print(" e: ");
    Serial.print(data.e);
    Serial.print(" f: ");
    Serial.println(data.f);
  }

}
