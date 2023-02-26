#!/bin/bash

SCORE=0

CASE_ID="cases800"

if [ "$1" != "" ]; then
    CASE_ID="$1"
fi

CASES=$(find "$CASE_ID" -name "*.txt")
for file in $CASES; do
    case_name=$(basename "$file")
    case_name="${case_name%.*}"

    echo -n "$case_name: "

    # status="$(head -n 1 "$CASE_ID/$case_name.info" | tail -n 1)"
    score="$(tail -n 1 "$CASE_ID/$case_name.log" | head -n 1)"
    score=${score##Total Cost: }
    echo "$score"
    echo "$score" > "$CASE_ID/$case_name.score"

    SCORE=$((SCORE + score))
done

echo
echo "SCORE: $SCORE"
