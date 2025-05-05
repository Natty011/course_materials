#!/bin/bash

# הגדרות
SOURCE_FILE="shuffle_sort.c"
EXEC_FILE="shuffle_sort.out"
WORDS_FILE="words"
COPIES=10
TMP_SORTED="sorted_output.tmp"
TMP_GROUPS="group_check.tmp"

# קומפילציה
echo "🔨 קומפילציה עם -ansi ו־-pedantic-errors..."
gcc -ansi -pedantic-errors -Wall -Wextra -I ../include/ "$SOURCE_FILE" -o "$EXEC_FILE"
if [ $? -ne 0 ]; then
    echo "❌ כשל בקומפילציה"
    exit 1
fi

# הרצה
echo "🚀 מריץ את $EXEC_FILE על $WORDS_FILE..."
./"$EXEC_FILE" "$WORDS_FILE" > "$TMP_SORTED"
if [ $? -ne 0 ]; then
    echo "❌ כשל בהרצה"
    exit 1
fi

# שלב בדיקה
echo "🔎 בודק שכל קבוצה של $COPIES מצביעים לאותה מילה..."

grep 'sorted_ptrs\[' "$TMP_SORTED" | awk -v cpy="$COPIES" '
BEGIN {
    ok = 1;
}
{
    split($0, parts, "=");
    idx = substr(parts[1], index(parts[1], "[") + 1);
    gsub("]", "", idx);
    gsub(" ", "", idx);
    word = parts[2];
    group = int(idx / cpy);
    sub(/^ /, "", word);
    g[group, idx % cpy] = word;
}
END {
    for (grp = 0; (grp,0) in g; ++grp) {
        base = g[grp, 0];
        for (j = 1; j < cpy; ++j) {
            if (g[grp, j] != base) {
                print "❌ קבוצה " grp ": mismatch - " base " vs " g[grp, j];
                ok = 0;
                break;
            }
        }
    }
    if (ok) {
        print "✅ כל הקבוצות תקינות (" cpy " מופעים זהים בכל קבוצה)";
        exit 0;
    }
    else {
        print "⚠️  נמצאו קבוצות שגויות.";
        exit 1;
    }
}
'
