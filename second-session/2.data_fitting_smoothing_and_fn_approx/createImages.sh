#!/bin/bash

DIR="images"
IMAGEFORMATTING="-x -11.0 11.0 --bitmap-size 820x820 -h 0.8 -w 0.8 -r 0.125 -u 0.10 -f 0.028 --title-font-size 0.055"

echo "Creating images ..."

graph -T png -L "Given data points"                  -y -1.2 1.2 $IMAGEFORMATTING < $DIR/function.dat         > $DIR/function.png
graph -T png -L "Polynomial interpolation"                       $IMAGEFORMATTING < $DIR/polynomialInterp.dat > $DIR/polynomialInterp1.png
graph -T png -L "Polynomial interpolation"           -y -1.5 1.5 $IMAGEFORMATTING < $DIR/polynomialInterp.dat > $DIR/polynomialInterp2.png
graph -T png -L "Polynomial interpolation"           -y -100 100 $IMAGEFORMATTING < $DIR/polynomialInterp.dat > $DIR/polynomialInterp3.png
graph -T png -L "Natural cubic spline interpolation" -y -1.2 1.2 $IMAGEFORMATTING < $DIR/cubicSpline.dat      > $DIR/cubicSpline.png

echo "Done"