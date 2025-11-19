; PlatformIO Project Configuration File
;
;   Build options: build flags, source filter
;   Upload options: custom upload port, speed and extra flags
;   Library options: dependencies, extra library storages
;   Advanced options: extra scripting
;
; Please visit documentation for the other options and examples
; https://docs.platformio.org/page/projectconf.html

[env:uno]  		
platform = atmelavr
board = uno
framework = arduino
monitor_speed = 9600
lib_deps =
	adafruit/Adafruit GFX Library@^1.12.1
	adafruit/DHT sensor library@^1.4.6
	adafruit/Adafruit SSD1306@^2.5.15


build_src_filter =
    +<*>
    +<../test/**>
	



///////////////////////////////////////////////////////
pio run
(clean מוחק קבצי ביניים ישנים שלא עודכנו מאז שינוי השם או הנתיב)
pio run -t clean
pio run

/////////////////////////
אם אתה רוצה גם לראות את הפלט בסימולציה או במסוף הסיריאלי:
pio run -t upload
pio device monitor
/////////////////////////////////////////////////////
ב־Wokwi אתה יכול פשוט ללחוץ על ▶️ “Run Simulation” — PlatformIO 
כבר מקמפל אוטומטית את שני הנתיבים (src + test).

//////////////////////////////////////////////
🧠 טיפ קטן

אם בעתיד תיצור כמה קבצי בדיקה שונים (למשל sensor_test.cpp או integration_test.cpp),
תוכל לשנות זמנית את שורת ה־build_src_filter כדי לבחור רק את אחד מהם לקומפילציה, למשל:
build_src_filter = +<src/**> +<test/sensor_test.cpp>

