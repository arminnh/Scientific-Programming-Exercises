#!/bin/bash

DIR="images"

#rm  images/*.png

for f in images/*.dat
do
    graph -T png -F HersheySans -L ${f:7:-4} --bitmap-size 820x820 < "$f" > ${f::-4}".png"
done

#rm  images/*.dat
