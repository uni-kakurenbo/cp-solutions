#!/bin/bash

SCORE=0

PARALLEL=1
CASE_ID="cases100"

if [ "$1" != "" ]; then
    CASE_ID="$1"
fi

if [ "$2" != "" ]; then
    PARALLEL="$2"
fi

function calc_score() {
    local case="$1"
    local file="$2"

    case_name=$(basename "$file")
    case_name="${case_name%.*}"

    status="$(head -n 1 "$case/$case_name.info" | tail -n 1)"

    touch "$case/$case_name.score"

    score="$(cargo run --release --bin score "$file" "$case/$case_name.res" 2> /dev/null)"

    if [ "$status" == 124 ]; then
        echo "$case_name: timed out"
    elif [ "$status" -gt 0 ]; then
        echo "$case_name: invalid exit: $status"
    fi

    echo "$case_name: $score;"
    echo "$score" > "$case/$case_name.score"
}

export -f calc_score

find "$CASE_ID" -name "*.txt" -print0 | xargs -0 -P "$PARALLEL" -I {} bash -c "calc_score '$CASE_ID' {}"

SCORE=0
# LOG_SCORE=0

CASES=$(find "$CASE_ID" -name "*.txt")
for file in $CASES; do
    case_name=$(basename "$file")
    case_name="${case_name%.*}"

    score="$(cat "$CASE_ID/$case_name.score")"
    SCORE=$((SCORE + score))
    # LOG_SCORE=$(echo "SCORE + l($score) / l(1.01)" | bc -l)
done

echo
echo "SCORE: $SCORE"
# echo "LOG_SCORE: $LOG_SCORE"
