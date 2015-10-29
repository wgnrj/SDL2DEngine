#!/bin/bash

for f in `ls --ignore *.sh`
do
    filename=$(basename "$f")
    extension="${filename##*.}"
    filename="${filename%.*}"
    convert "$filename.$extension" \
        -crop 100x100+150+100 \
        -fuzz 8% -transparent '#9FA1A3' \
        -fuzz 8% -transparent '#B2B4B6' \
        -fuzz 8% -transparent '#D4D5D7' \
        -fuzz 8% -transparent '#E6E7E8' \
        -fuzz 8% -transparent '#FFFFFF' \
        "$filename-small.$extension"
    convert *-small.png result.png
done

