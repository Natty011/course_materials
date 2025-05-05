#!/bin/bash

# טסט: האם wd_test מחייה את watchdog_app לאחר הריגה ידנית?

WATCHDOG_APP="./watchdog_app.out"
CLIENT_APP="./wd_test.out"
PING_FREQ=3
ALLOWED_MISSES=20
LOGFILE="revive_test.log"

echo ">> Starting test: $CLIENT_APP $PING_FREQ $ALLOWED_MISSES $WATCHDOG_APP"
$CLIENT_APP $PING_FREQ $ALLOWED_MISSES $WATCHDOG_APP > "$LOGFILE" 2>&1 &

CLIENT_PID=$!
echo "[TEST] wd_test.out started with PID: $CLIENT_PID"

# נחכה לוודאות שהמערכת רצה
sleep 5

# מחפש את תהליך ה-watchdog שהוקם
WD_PID=$(pgrep -f "$WATCHDOG_APP" | grep -v "$CLIENT_PID" | head -n 1)
if [ -z "$WD_PID" ]; then
    echo "[ERROR] No watchdog_app.out process found!"
    kill $CLIENT_PID
    exit 1
fi

echo "[TEST] Found watchdog_app.out with PID: $WD_PID"

# הורג את ה-WD
echo "[TEST] Killing watchdog_app.out..."
kill -9 "$WD_PID"

# ממתין להחייאה
sleep 5

# בודק אם watchdog_app חזר
NEW_WD_PID=$(pgrep -f "$WATCHDOG_APP" | grep -v "$CLIENT_PID" | head -n 1)

if [ -n "$NEW_WD_PID" ] && [ "$NEW_WD_PID" != "$WD_PID" ]; then
    echo "[SUCCESS] watchdog_app.out revived successfully with new PID: $NEW_WD_PID"
else
    echo "[FAIL] watchdog_app.out was NOT revived."
fi

# ניקוי
kill "$CLIENT_PID" 2>/dev/null
echo ">> Test completed. Check $LOGFILE for full logs."

