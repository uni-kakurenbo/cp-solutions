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

    score="$(tail -n 5 "$case/$case_name.log" | head -n 1 2> /dev/null | sed -e "s/[^0-9]//g")"
    wa_cnt="$(tail -n 4 "$case/$case_name.log" | head -n 1 2> /dev/null | sed -e "s/[^0-9]//g")"
    p_cost="$(tail -n 3 "$case/$case_name.log" | head -n 1 2> /dev/null | sed -e "s/[^0-9]//g")"
    m_cost="$(tail -n 2 "$case/$case_name.log" | head -n 1 2> /dev/null | sed -e "s/[^0-9]//g")"
    m_cnt="$(tail -n 1 "$case/$case_name.log" | head -n 1 2> /dev/null | sed -e "s/[^0-9]//g")"

    if [ "$status" == 124 ]; then
        echo "$case_name: timed out"
    elif [ "$status" -gt 0 ]; then
        echo "$case_name: invalid exit: $status"
    fi

    echo "$case_name: $score; $wa_cnt, $p_cost, $m_cost, $m_cnt;"
    {
        echo "$score"
        echo "$wa_cnt"
        echo "$p_cost"
        echo "$m_cost"
        echo "$m_cnt"
    } >> "$case/$case_name.score"

}

export -f calc_score

find "$CASE_ID" -name "*.txt" -print0 | xargs -0 -P "$PARALLEL" -I {} bash -c "calc_score '$CASE_ID' {}"

SCORE=0
CASE_CNT=0
EXP_SCORE=0
P_COST=0
M_COST=0
M_CNT=0

CASES=$(find "$CASE_ID" -name "*.txt")
for file in $CASES; do
    case_name=$(basename "$file")
    case_name="${case_name%.*}"

    score="$(tail -n 5 "$CASE_ID/$case_name.score" | head -n 1)"
    wa_cnt="$(tail -n 4 "$CASE_ID/$case_name.score" | head -n 1)"
    p_cost="$(tail -n 3 "$CASE_ID/$case_name.score" | head -n 1)"
    m_cost="$(tail -n 2 "$CASE_ID/$case_name.score" | head -n 1)"
    m_cnt="$(tail -n 1 "$CASE_ID/$case_name.score" | head -n 1)"

    CASE_CNT=$((CASE_CNT + 1))

    SCORE=$((SCORE + score))
    EXP_SCORE=$(echo "$EXP_SCORE + e($score * l(1.0000001))" | bc -l)

    WA_CNT=$((WA_CNT + wa_cnt))
    P_COST=$((P_COST + p_cost))
    M_COST=$((M_COST + m_cost))
    M_CNT=$((M_CNT + m_cnt))
done

echo
echo "TOTAL_SCORE: $SCORE"
echo "AVELAGE_SCOR: $((SCORE / CASE_CNT))"
echo "AVELAGE_WA_CNT: $((WA_CNT / CASE_CNT))"
echo "AVELAGE_P_COST: $((P_COST / CASE_CNT))"
echo "AVELAGE_M_COST: $((M_COST / CASE_CNT))"
echo "AVELAGE_M_CNT: $((M_CNT / CASE_CNT))"
echo "TOTAL_EXP_SCORE: $EXP_SCORE"
