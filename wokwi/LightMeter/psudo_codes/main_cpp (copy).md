אתחל תקשורת Serial
צור אובייקט Sensor בשם sensor עם הפינים A0 ו־D2

לולאה ראשית:
    sensor.ReadAnalog()
    sensor.ReadDigital()
    lightPercent ← sensor.GetLightLevelPercent()
    sensor.PrintDebug()
    המתן 500ms
