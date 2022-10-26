#!/bin/bash

EXECUTION_COMMAND="$1"
PARALLEL=3

if [ "$2" != "" ]; then
    PARALLEL="$2"
fi

echo "Parallel execution: $PARALLEL"


function run_case() {
    local executin_command=$1
    local file="$2"

    case_name=$(basename "$file")
    case_name="${case_name%.*}"

    echo "$case_name"

    # shellcheck disable=SC2086
    timeout 3 $executin_command <"$file" >"cases/$case_name.res" 2>"cases/$case_name.log"
    echo $? >"cases/$case_name.status"
}

export -f run_case

find cases/ -name "*.txt" -print0 | xargs -0 -L 1 -P "$PARALLEL" -I {} bash -c "run_case '$EXECUTION_COMMAND' {}"

./calc_score.sh
