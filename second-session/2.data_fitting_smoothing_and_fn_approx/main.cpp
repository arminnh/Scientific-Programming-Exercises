#include <iostream>
#include "./functions.h"

int main (void) {
    const int m = 21;
    double x_i[m], y_i[m];
    fillFArrays(x_i, y_i, m);
    double a = minArray(x_i, m);
    double b = maxArray(x_i, m);

    std::ofstream dataPoints;
    dataPoints.open("images/dataPoints.dat");

    if(!dataPoints.is_open()) {
        std::cout << "Could not open file 'dataPoints.dat', make sure the images folder exists" << std::endl;
        return false;
    }

    dataPoints << "#m=0,S=2\n";
    for (int i = 0; i < m; i++) {
        dataPoints << x_i[i] << " " << y_i[i] << "\n";
        std::cout << "x_i[" << i << "] = " << x_i[i] << ", y_i[" << i << "] = " << y_i[i] << "\n";
    }
    std::cout << "a = " << a << ", b = " << b << "\n";


    polynomialAndSplineSolutions(m, x_i, y_i);

    int leastSquares[6] = {5, 9, 10, 11, 15, 20};
    for (int i = 0; i < 6; i++) {
        leastSquaresSolutions(m, leastSquares[i], x_i, a, b, y_i);
        leastSquaresSolutions(m, leastSquares[i], x_i, a, b, y_i, true);
    }

    dataPoints.close();
    // create the images with the gsl plotutils graph application
    system("./createImages.sh");
    return 0;
}
