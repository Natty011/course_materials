#!/bin/bash

# טסט דו-צדדי: כל צד הורג את השני, ובודקים אם בוצעה החייאה
WATCHDOG_APP="./watchdog_app.out"
CLIENT_APP="./wd_test.out"
PING_FREQ=3
ALLOWED_MISSES=20
LOGFILE="bidirectional_revive_test.log"

echo ">> Starting bidirectional revive test"
echo "[INFO] Launching: $CLIENT_APP $ALLOWED_MISSES $PING_FREQ $WATCHDOG_APP"
$CLIENT_APP $ALLOWED_MISSES $PING_FREQ $WATCHDOG_APP > "$LOGFILE" 2>&1 &

# מחכים שהכל יתייצב
sleep 5

# מוצאים PID של כל תהליך
get_pid() {
    pgrep -f "$1" | grep -v "$$" | head -n 1
}

CLIENT_PID=$(get_pid "$CLIENT_APP")
WD_PID=$(get_pid "$WATCHDOG_APP")

echo "[INFO] Client PID: $CLIENT_PID"
echo "[INFO] Watchdog PID: $WD_PID"

# ---- שלב א': הורג את wd_test.out ובודק אם watchdog מחייה אותו ----
echo "[STEP 1] Killing wd_test.out (PID: $CLIENT_PID)..."
kill -9 "$CLIENT_PID"
sleep 6

NEW_CLIENT_PID=$(get_pid "$CLIENT_APP")

if [ -n "$NEW_CLIENT_PID" ] && [ "$NEW_CLIENT_PID" != "$CLIENT_PID" ]; then
    echo "[SUCCESS] Client revived by watchdog: $NEW_CLIENT_PID"
else
    echo "[FAIL] Client was not revived."
fi

# ---- שלב ב': הורג את watchdog_app.out ובודק אם wd_test מחייה אותו ----
echo "[STEP 2] Killing watchdog_app.out (PID: $WD_PID)..."
kill -9 "$WD_PID"
sleep 6

NEW_WD_PID=$(get_pid "$WATCHDOG_APP")

if [ -n "$NEW_WD_PID" ] && [ "$NEW_WD_PID" != "$WD_PID" ]; then
    echo "[SUCCESS] Watchdog revived by client: $NEW_WD_PID"
else
    echo "[FAIL] Watchdog was not revived."
fi

# ---- ניקוי ----
echo "[CLEANUP] Killing all remaining processes..."
killall "$CLIENT_APP" "$WATCHDOG_APP" 2>/dev/null
echo ">> Test completed. Check $LOGFILE for detailed output."

