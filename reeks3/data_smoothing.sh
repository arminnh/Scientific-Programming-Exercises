#!/bin/bash

DIR="images"

for n in 2 4 7
do
    ./data_smoothing.bin $n rescale
    graph -T png -x -1 1 -y -0.5 3  -F HersheySans -L "Model g(x) for log(y(x))" --bitmap-size 820x820 < $DIR/gx_degree$n"_rescaled.dat" > $DIR/gx_degree$n"_rescaled.png"
    graph -T png -x -1 1 -y 0 10  -F HersheySans -L "Original datapoints and exp(g(x))" --bitmap-size 820x820 < $DIR/exp_gx_degree$n"_rescaled.dat" > $DIR/exp_gx_degree$n"_rescaled.png"

    ./data_smoothing.bin $n
    graph -T png -x 0.5 5.5 -y -0.5 3  -F HersheySans -L "Model g(x) for log(y(x))" --bitmap-size 820x820 < $DIR/gx_degree$n.dat > $DIR/gx_degree$n.png
    graph -T png -x 0.5 5.5 -y 0 10  -F HersheySans -L "Original datapoints and exp(g(x))" --bitmap-size 820x820 < $DIR/exp_gx_degree$n.dat > $DIR/exp_gx_degree$n.png

done

graph -T png -x 0 8 -y 0 10 -F HersheySans -L "Input Datapoints" --bitmap-size 820x820 < $DIR/datapoints.dat > $DIR/datapoints.png
graph -T png -x 0 6 -y -0.5 3 -F HersheySans -L "Log of input values y(x)" --bitmap-size 820x820 < $DIR/log_datapoints.dat > $DIR/log_datapoints.png