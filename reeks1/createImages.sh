#!/bin/bash

DIR="images"

graph -T png -F HersheySans -L "Runge Function" --bitmap-size 820x820 < $DIR/runge.dat > $DIR/runge.png

graph -T png -F HersheySans -L "Natural Cubic Spline" --bitmap-size 820x820 < $DIR/spline1.dat > $DIR/spline1.png
graph -T png -F HersheySans -L "Cubic Spline With Modified Conditions" --bitmap-size 820x820 < $DIR/spline2.dat > $DIR/spline2.png

graph -T png -F HersheySans -L "Polynomial through equidistant points" --bitmap-size 820x820 < $DIR/poly1.dat > $DIR/poly1.png
graph -T png -F HersheySans -L "Polynomial through non equidistant points" --bitmap-size 820x820 < $DIR/poly2.dat > $DIR/poly2.png

graph -T png -F HersheySans -L "first polynomial - absolute difference" --bitmap-size 820x820 < $DIR/diff1abs.dat > $DIR/diff1abs.png
graph -T png -F HersheySans -L "second polynomial -absolute difference" --bitmap-size 820x820 < $DIR/diff2abs.dat > $DIR/diff2abs.png
graph -T png -F HersheySans -L "first spline - absolute diffrence" --bitmap-size 820x820 < $DIR/diff3abs.dat > $DIR/diff3abs.png
graph -T png -F HersheySans -L "second spline - absolute diffrence" --bitmap-size 820x820 < $DIR/diff4abs.dat > $DIR/diff4abs.png

graph -T png -F HersheySans -L "first polynomial - relative difference" --bitmap-size 820x820 < $DIR/diff1rel.dat > $DIR/diff1rel.png
graph -T png -F HersheySans -L "second polynomial - relative difference" --bitmap-size 820x820 < $DIR/diff2rel.dat > $DIR/diff2rel.png
graph -T png -F HersheySans -L "first spline - relative difference" --bitmap-size 820x820 < $DIR/diff3rel.dat > $DIR/diff3rel.png
graph -T png -F HersheySans -L "second spline - relative difference" --bitmap-size 820x820 < $DIR/diff4rel.dat > $DIR/diff4rel.png