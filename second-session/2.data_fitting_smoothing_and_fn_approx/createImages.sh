#!/bin/bash

DIR="images"
IMAGEFORMATTING="-T png  --bitmap-size 820x820 -h 0.8 -w 0.8 -r 0.125 -u 0.10 -f 0.028 --title-font-size 0.055"

echo "Creating images ..."

graph -L "Given data points"                  -x -11.0 11.0 -y -1.2 1.2 $IMAGEFORMATTING < $DIR/dataPoints.dat       > $DIR/dataPoints.png
graph -L "Polynomial interpolation"           -x -11.0 11.0             $IMAGEFORMATTING < $DIR/polynomialInterp.dat > $DIR/polynomialInterp1.png
graph -L "Polynomial interpolation"           -x -11.0 11.0 -y -1.5 1.5 $IMAGEFORMATTING < $DIR/polynomialInterp.dat > $DIR/polynomialInterp2.png
graph -L "Polynomial interpolation"           -x -11.0 11.0 -y -100 100 $IMAGEFORMATTING < $DIR/polynomialInterp.dat > $DIR/polynomialInterp3.png
graph -L "Natural cubic spline interpolation" -x -11.0 11.0 -y -1.2 1.2 $IMAGEFORMATTING < $DIR/cubicSpline.dat      > $DIR/cubicSpline.png

for n in 3 5 10
do
    graph -L "Least squares approx with n = "$n -x -1.1 1.1 -y -1.1 1.1 $IMAGEFORMATTING < $DIR/leastSquares_degree_$n.dat > $DIR/leastSquares_degree_$n.png
done

for n in 15 20 21
do
    graph -L "Least squares approx with n = "$n -x -1.1 1.1             $IMAGEFORMATTING < $DIR/leastSquares_degree_$n.dat > $DIR/leastSquares_degree_$n"_zoomed_out".png
    graph -L "Least squares approx with n = "$n -x -1.1 1.1 -y -1.1 1.1 $IMAGEFORMATTING < $DIR/leastSquares_degree_$n.dat > $DIR/leastSquares_degree_$n.png
done

#graph -x -0.3 6.7 $IMAGEFORMATTING < $DIR/trigApprox_n_5_m_1.dat > $DIR/trigApprox_n_5_m_1.png
#graph -x -0.3 6.7 $IMAGEFORMATTING < $DIR/trigApprox_n_5_m_2.dat > $DIR/trigApprox_n_5_m_2.png

#graph -x -0.3 6.7 $IMAGEFORMATTING < $DIR/trigApprox_n_8_m_2.dat > $DIR/trigApprox_n_8_m_2.png
#graph -x -0.3 6.7 $IMAGEFORMATTING < $DIR/trigApprox_n_8_m_4.dat > $DIR/trigApprox_n_8_m_4.png

for n in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
do
    graph -x -0.3 6.7 -y -2.5 2.5 $IMAGEFORMATTING < $DIR/trigApprox_n_21_m_$n.dat > $DIR/trigApprox_n_21_m_$n.png
done

echo "Done"