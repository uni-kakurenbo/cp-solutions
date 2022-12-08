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

    cargo run --release --bin vis "$CASE_ID/$case_name".txt "$CASE_ID/$case_name".res > "$CASE_ID/$case_name.score" 2> /dev/null
    # status="$(head -n 1 "$CASE_ID/$case_name.info" | tail -n 1)"
    score="$(tail -n 1 "$CASE_ID/$case_name.score" | head -n 1)"
    score=${score##Score = }
    echo "$score"

    SCORE=$((SCORE + score))
done

echo
echo "SCORE: $SCORE"
