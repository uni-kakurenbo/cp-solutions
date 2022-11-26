#!/bin/bash

i=0
for ((m=10; m <= 100; m++)); do
    for ((e=0; e <= 40; e++)); do
        index=$(printf "%04d" "${i}")
        eps=$(printf "%02d" "${e}")
        cargo run --release --bin gen seed.txt "--M=$m" "--eps=0.$eps" "--dir=gen_temp"
        cp "gen_temp/0000.txt" "./cases_all/$index.txt"
        i=$((i + 1))
    done
done
