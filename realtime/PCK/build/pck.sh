#! /bin/bash

TARGET=$1
OUTPUT_PATH=$2
shift 2

ccache g++-11 -fdiagnostics-color=always -Wno-misleading-indentation -Wall -Wextra -Wno-char-subscripts -fsplit-stack -o "$OUTPUT_PATH" "$@" "$TARGET"
