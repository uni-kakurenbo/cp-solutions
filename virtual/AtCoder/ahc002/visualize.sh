#!/bin/bash

CASE=""
FILE=".history"

if [ "$1" != "" ]; then
    CASE="$1"
fi
if [ "$2" != "" ]; then
    FILE="$2"
fi

mkdir -p vis

cnt=0
while read -rd $'\n' line; do
    echo "$cnt"
    echo "$line" > vis.temp
    cargo run --release --bin vis "$CASE" vis.temp 2> /dev/null
    mv out.svg "vis/$cnt.svg"
    cnt=$((cnt + 1))
done < <(cat "$FILE")

function to_png() {
    cairosvg "vis/$1.svg" -o "vis/$1.png"
}

export -f to_png

seq 0 $((cnt-1)) | xargs -P 5 -I {} bash -c "to_png {}"

ffmpeg -r 30 -i ./vis/%d.png -vcodec libx264 -pix_fmt yuv420p -r 30 vis.mp4
