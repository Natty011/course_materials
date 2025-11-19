// <Arduino.h> — setup/loop, millis
#include <Arduino.h>     // setup(), loop(), millis()
// "ui.h" — שכבת הקלט/פלט והחומרה
#include "ui.h"          // nlrd::UserInterface
// "dispenser.h" — הקונטקסט שמנהל מצבים ואירועים
#include "dispenser.h"  // SodaDispenser::Dispenser

// קיצור שמות
using SodaDispenser::Dispenser;
using UI = nlrd::UserInterface;

// מופעים גלובליים (במערכת Embedded זה סביר)
UI g_ui;
Dispenser g_disp(g_ui);

void setup() {
  g_disp.Begin();
}

void loop() {
  const uint32_t now = millis();
  g_disp.Tick(now);
  delay(10); // קצב דגימה סביר
}
