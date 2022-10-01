#!/bin/bash

SCORE=0

CASE_ID="cases100"

if [ "$1" != "" ]; then
    CASE_ID="$1"
fi

CASES=$(find "$CASE_ID" -name "*.txt")
for file in $CASES; do
    case_name=$(basename "$file")
    case_name="${case_name%.*}"

    echo -n "$case_name: "

    status="$(head -n 1 "$CASE_ID/$case_name.info" | tail -n 1)"

    if [ "$status" == 124 ]; then
        echo -n "timed out"
    elif [ "$status" -gt 0 ]; then
        echo -n "invalid exit: $status"
    fi

    touch "$CASE_ID/$case_name.score"

    score="$(./visualizer.exe "$file" "$CASE_ID/$case_name.res" | sed -e "s/[^0-9]//g")"
    echo "$score;"
    echo "$score" > "$CASE_ID/$case_name.score"

    SCORE=$((SCORE + score))
done

echo
echo "SCORE: $SCORE"
