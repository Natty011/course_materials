#ifndef UNITY_CONFIG_H
#define UNITY_CONFIG_H

// ודא ש-Arduino.h נטען לפני שימוש ב-Serial
#ifdef ARDUINO
  #include <Arduino.h>
#endif

// נשתמש בהגדרות בטוחות: Unity תשתמש ב-Serial רק כשהוא קיים
#ifdef ARDUINO
  #define UNITY_OUTPUT_START()    Serial.begin(9600)
  #define UNITY_OUTPUT_CHAR(c)    Serial.write(c)
  #define UNITY_OUTPUT_FLUSH()    Serial.flush()
  #define UNITY_OUTPUT_COMPLETE()
#else
  // אם לא רץ על פלטפורמת Arduino – הדפס למסוף רגיל
  #include <stdio.h>
  #define UNITY_OUTPUT_START()
  #define UNITY_OUTPUT_CHAR(c)    putchar(c)
  #define UNITY_OUTPUT_FLUSH()    fflush(stdout)
  #define UNITY_OUTPUT_COMPLETE()
#endif

#endif // UNITY_CONFIG_H
