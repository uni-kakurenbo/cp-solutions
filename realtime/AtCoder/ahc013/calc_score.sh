#!/bin/bash

SCORE=0

while read -rd $'\0' file; do
    case_name=$(basename "$file")
    case_name="${case_name%.*}"

    echo -n "$case_name; "

    status="$(cat "cases/$case_name.status")"
    if [ "$status" == 124 ]; then
        echo -n "timed out"
    elif [ "$status" -gt 0 ]; then
        echo -n "invalid exit: $status"
    fi

    score=$(tail "cases/$case_name.log" -n 1)
    echo "$score"

    SCORE=$((SCORE + score))

done < <(find cases/ -name "*.txt" -print0)

echo
echo "SCORE: $SCORE"
