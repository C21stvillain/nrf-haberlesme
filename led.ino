#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(10, 9); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
Servo myServo;

void setup() {
  myServo.attach(7);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  delay(5);
  radio.stopListening();
  int potValue = analogRead(A0);
  int angleV = map(potValue, 0, 1023, 0, 180);
  radio.write(&angleV, sizeof(angleV));

  delay(5);
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()) {
      int angleV = 0;
      radio.read(&angleV, sizeof(angleV));
      myServo.write(angleV);
      Serial.print(angleV);
}
}
}
