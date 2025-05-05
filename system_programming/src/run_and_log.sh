#!/bin/bash

PROGRAM="./shuffle_sort.out"
DICT="/usr/share/dict/words"
LOG="shuffle_log.txt"
VALGRIND_LOG="valgrind_log.txt"

echo "🔄 קומפילציה..."
gd shuffle_sort.c -I ../include/ -o shuffle_sort.out

if [ $? -ne 0 ]; then
    echo "❌ כשל בקומפילציה"
    exit 1
fi

echo "🚀 מריץ את התוכנית עם לוגים..."
$PROGRAM $DICT > "$LOG" 2>&1
echo "📄 הפלט נכתב אל $LOG"

echo "🧠 מריץ valgrind..."
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all \
    $PROGRAM $DICT > "$VALGRIND_LOG" 2>&1

echo "📄 לוג של valgrind נכתב אל $VALGRIND_LOG"
