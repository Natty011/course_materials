#!/bin/bash

set -e

MAKE_DIR="./make"
BIN="./bin/debug"
TEST_APP="$BIN/wd_test.out"
WATCHDOG_APP="$BIN/watchdog_app.out"

echo "Building wd_test.out..."
make -C $MAKE_DIR bin/debug/wd_test.out

echo "Running watchdog_app.out with wd_test.out..."
$WATCHDOG_APP 2 3 $TEST_APP
