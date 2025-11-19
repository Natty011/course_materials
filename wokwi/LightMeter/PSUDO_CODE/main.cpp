const int ldrPin = A0;
const int ledPin = 11;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  
  // הפוך את הערך כך שככל שחושך – הלד חזק יותר
  int inverted = 1023 - ldrValue;

  // מיפוי הערך מ־0–1023 לטווח של PWM (0–255)
  int ledBrightness = map(inverted, 0, 1023, 0, 255);

  analogWrite(ledPin, ledBrightness);

  Serial.print("LDR: ");
  Serial.print(ldrValue);
  Serial.print(" -> LED PWM: ");
  Serial.println(ledBrightness);

  delay(200);
}

