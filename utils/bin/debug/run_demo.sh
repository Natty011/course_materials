#!/bin/bash

#chmod +x run_demo.sh
#./run_demo.sh

BIN="./watchdog_app.out"

if [ ! -f "$BIN" ]; then
    echo "Executable $BIN not found! Compile first."
    exit 1
fi

echo "Running Watchdog Demo..."
$BIN 2 3

echo "Done."

