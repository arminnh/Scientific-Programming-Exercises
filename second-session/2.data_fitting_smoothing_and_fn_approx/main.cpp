#include <iostream>
#include "./functions.h"
#include "math.h"

int main (void) {
    const int m = 21;
    double x_i[m], y_i[m];
    fillFArrays(x_i, y_i, m);    // x_i = i - 10, y_i = (-1)^i, i = 0..20
    double a = minArray(x_i, m); // -10
    double b = maxArray(x_i, m); // 10

    // write given points to dataPoins.dat
    writeDataPoints(x_i, y_i, m);

    // polynomial interpolation and spline interpolation
    polynomialAndSplineSolutions(m, x_i, y_i);

    // least squares approximations
    int leastSquares[] = {3, 5, 10, 15, 20, 21};
    for (int i = 0; i < 6; i++) {
        leastSquaresApproximation(m, leastSquares[i], x_i, a, b, y_i);
    }

    // trigonometric polynomial interpolation and trigonometric least squares approximation0
    trigonometricApproximation(m, 1, x_i, a, b, y_i);
    trigonometricApproximation(m, 2, x_i, a, b, y_i);
    trigonometricApproximation(m, 3, x_i, a, b, y_i);
    trigonometricApproximation(m, 4, x_i, a, b, y_i);
    trigonometricApproximation(m, 5, x_i, a, b, y_i);
    trigonometricApproximation(m, 6, x_i, a, b, y_i);
    trigonometricApproximation(m, 7, x_i, a, b, y_i);
    trigonometricApproximation(m, 8, x_i, a, b, y_i);
    trigonometricApproximation(m, 9, x_i, a, b, y_i);
    trigonometricApproximation(m, 10, x_i, a, b, y_i);
    trigonometricApproximation(m, 11, x_i, a, b, y_i);
    trigonometricApproximation(m, 12, x_i, a, b, y_i);
    trigonometricApproximation(m, 13, x_i, a, b, y_i);
    trigonometricApproximation(m, 14, x_i, a, b, y_i);
    trigonometricApproximation(m, 15, x_i, a, b, y_i);

    // 4 examples of fourrier approximation from the book, works perfectly...
    /*
    double tt[] = {0, 2*M_PI/5, 4*M_PI/5, 6*M_PI/5, 8*M_PI/5}, xx[] = {1, 3, 2, 0, -1};
    trigonometricApproximation(5, 1, tt, 0, 2*M_PI, xx);
    trigonometricApproximation(5, 2, tt, 0, 2*M_PI, xx);

    double ttt[] = {0 * (2*M_PI)/8, 1 * (2*M_PI)/8, 2 * (2*M_PI)/8, 3 * (2*M_PI)/8, 4 * (2*M_PI)/8, 5 * (2*M_PI)/8, 6 * (2*M_PI)/8, 7 * (2*M_PI)/8}, xxx[] = {1, 1, 1, 1, 0, 0, 0, 0};
    trigonometricApproximation(8, 2, ttt, 0, 2*M_PI, xxx);
    trigonometricApproximation(8, 4, ttt, 0, 2*M_PI, xxx);
     */

    // create the images with the gsl plotutils graph application
    system("./createImages.sh");
    return 0;
}
