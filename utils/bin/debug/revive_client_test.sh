#!/bin/bash

# טסט: האם watchdog_app מחייה את wd_test אחרי הריגה ידנית?

WATCHDOG_APP="./watchdog_app.out"
CLIENT_APP="./wd_test.out"
PING_FREQ=3
ALLOWED_MISSES=20
LOGFILE="revive_client_test.log"

echo ">> Starting test: $CLIENT_APP $ALLOWED_MISSES $PING_FREQ $WATCHDOG_APP"
$CLIENT_APP $ALLOWED_MISSES $PING_FREQ $WATCHDOG_APP > "$LOGFILE" 2>&1 &

CLIENT_PID=$!
echo "[TEST] wd_test.out started with PID: $CLIENT_PID"

# מחכים קצת שהמערכת תיכנס ללופ
sleep 5

# מוצאים את PID של wd_test שהורץ מחדש (אם כבר הוחלף)
WD_TEST_PIDS=$(pgrep -f "$CLIENT_APP")
for PID in $WD_TEST_PIDS
do
    if [ "$PID" != "$$" ]; then
        CLIENT_PID="$PID"
    fi
done

# הורג את wd_test.out
echo "[TEST] Killing wd_test.out (PID: $CLIENT_PID)..."
kill -9 "$CLIENT_PID"

# מחכה לתגובה והחייאה
sleep 6

# מחפש PID חדש
NEW_CLIENT_PID=$(pgrep -f "$CLIENT_APP" | grep -v "$$" | head -n 1)

if [ -n "$NEW_CLIENT_PID" ] && [ "$NEW_CLIENT_PID" != "$CLIENT_PID" ]; then
    echo "[SUCCESS] wd_test.out revived successfully with new PID: $NEW_CLIENT_PID"
else
    echo "[FAIL] wd_test.out was NOT revived."
fi

# ניקוי
killall "$CLIENT_APP" "$WATCHDOG_APP" 2>/dev/null
echo ">> Test completed. Check $LOGFILE for full logs."

