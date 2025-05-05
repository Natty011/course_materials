#!/bin/bash

# Compile if needed
gcc shuffle_sort.c -I ../include -o shuffle_sort.out -Wall -Wextra -ansi -pedantic-errors

# Run the program and extract the first 10 lines of sorted_ptrs
./shuffle_sort.out ./words > temp_output.txt

# Check the first 10 sorted_ptrs entries
echo "🔍 Checking that first 10 sorted_ptrs entries are identical..."

head -n 30 temp_output.txt | grep sorted_ptrs > sorted_first_10.txt

# Extract just the strings
cut -d '=' -f2 sorted_first_10.txt | sed 's/^ //' > just_words.txt

# Compare all lines to the first one
first_word=$(head -n1 just_words.txt)
all_match=true

while read -r line; do
    if [ "$line" != "$first_word" ]; then
        echo "❌ Mismatch found: $line vs $first_word"
        all_match=false
    fi
done < just_words.txt

if [ "$all_match" = true ]; then
    echo "✅ All 10 entries are identical: '$first_word'"
else
    echo "⚠️ Not all entries are identical."
fi

# Clean up
rm -f temp_output.txt sorted_first_10.txt just_words.txt
