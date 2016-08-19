#!/bin/bash

DIR="images"
IMAGEFORMATTING="-T png  --bitmap-size 820x820 -h 0.8 -w 0.8 -r 0.125 -u 0.10 -f 0.028 --title-font-size 0.055"

echo "Creating images ..."

graph -L "Given data points"                  -x -11.0 11.0 -y -1.2 1.2 $IMAGEFORMATTING < $DIR/dataPoints.dat       > $DIR/dataPoints.png
graph -L "Polynomial interpolation"           -x -11.0 11.0             $IMAGEFORMATTING < $DIR/polynomialInterp.dat > $DIR/polynomialInterp1.png
graph -L "Polynomial interpolation"           -x -11.0 11.0 -y -1.5 1.5 $IMAGEFORMATTING < $DIR/polynomialInterp.dat > $DIR/polynomialInterp2.png
graph -L "Polynomial interpolation"           -x -11.0 11.0 -y -100 100 $IMAGEFORMATTING < $DIR/polynomialInterp.dat > $DIR/polynomialInterp3.png
graph -L "Natural cubic spline interpolation" -x -11.0 11.0 -y -1.2 1.2 $IMAGEFORMATTING < $DIR/cubicSpline.dat      > $DIR/cubicSpline.png

for n in 5 9 10 11 15 20
do
    echo $DIR/gx_degree$n.dat" > "$DIR/gx_degree$n.png
    graph -x -11.0 11.0 -y -1.2 1.2 $IMAGEFORMATTING < $DIR/leastSquares$n.dat > $DIR/leastSquares$n.png
    graph -x -1.1 1.1   -y -1.2 1.2 $IMAGEFORMATTING < $DIR/leastSquares$n"_rescaled.dat" > $DIR/leastSquares$n"_rescaled.png"
done

echo "Done"