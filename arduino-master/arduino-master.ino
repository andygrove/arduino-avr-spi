#include <SPI.h>

const int chipSelectPin = 10;

void setup() {
  Serial.begin(9600);
  pinMode(chipSelectPin, OUTPUT);
  digitalWrite(chipSelectPin, HIGH);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  SPI.begin();
}

void send(unsigned int n) {
  Serial.print("Sending ");
  Serial.print(n, HEX);
  digitalWrite(chipSelectPin, LOW);
  unsigned int response = SPI.transfer(n);
  digitalWrite(chipSelectPin, HIGH);
  Serial.print(" .. received ");
  Serial.println(response, HEX);
  delay(100);
}

void loop() {
//  send(170);
//  send(255);
    for (int i=0; i<255; i++) {
      send(i);
    }
}
