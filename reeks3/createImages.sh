#!/bin/bash

DIR="images"

graph -T png -x 0 8 -y 0 10 -F HersheySans -L "Input Datapoints" --bitmap-size 820x820 < $DIR/datapoints.dat > $DIR/datapoints.png
graph -T png -x 0 6 -y -0.5 3 -F HersheySans -L "Log of input values y(x)" --bitmap-size 820x820 < $DIR/log_datapoints.dat > $DIR/log_datapoints.png
graph -T png -x 0 6 -y -0.5 3  -F HersheySans -L "Model g(x) for log(y(x))" --bitmap-size 820x820 < $DIR/gx.dat > $DIR/gx.png
graph -T png -x 0 8 -y 0 10  -F HersheySans -L "Original datapoints and exp(g(x))" --bitmap-size 820x820 < $DIR/exp_gx.dat > $DIR/exp_gx.png
