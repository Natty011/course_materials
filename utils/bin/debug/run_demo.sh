#!/bin/bash

# Demo script to run watchdog project
# Run from: bin/debug/
# Make sure all executables are up to date and in the same directory

PING_FREQ=2
ALLOWED_MISSES=3
CLIENT_PROG=./wd_test.out
WATCHDOG_APP=./watchdog_app.out
LOG=log.txt

# Clean previous log
rm -f $LOG

echo ">> Starting $WATCHDOG_APP"
$WATCHDOG_APP $PING_FREQ $ALLOWED_MISSES $CLIENT_PROG > $LOG 2>&1 &

WD_PID=$!
echo "Watchdog App PID: $WD_PID"

# Allow time for client and watchdog to communicate
sleep 5

# Get client PID from ps (child of watchdog_app)
CLIENT_PID=$(pgrep -P $WD_PID wd_test.out)
echo "Client PID: $CLIENT_PID"

if [ -z "$CLIENT_PID" ]; then
    echo "Client process not found. Something went wrong."
else
    echo ">> Killing client process ($CLIENT_PID) to trigger revive..."
    kill -9 $CLIENT_PID
fi

# Wait and observe revive
sleep 8

echo ">> Showing last lines of log:"
tail -n 20 $LOG

