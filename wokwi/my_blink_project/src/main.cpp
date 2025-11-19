#include <Arduino.h>

void setup() {
  pinMode(13, OUTPUT); // במקום LED_BUILTIN
}

void loop() {
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}

