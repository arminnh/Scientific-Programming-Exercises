#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_deriv.h>
#include <gsl/gsl_spline.h>
#include <algorithm>
#include <fstream>
#include <iostream>

int f(int i)
{
    return (int) pow(-1, i);
}

void fillFArrays(double *x_i, double *y_i, int length)
{
    for (int i = 0; i < length; i++) {
        x_i[i] = i - 10;
        y_i[i] = f(i - 10);
    }
}

bool openFiles(std::ofstream &function, std::ofstream &polynomialInterp, std::ofstream &cubicSpline, std::ofstream &leastSquares, std::ofstream &trigInterp, std::ofstream &trigLeastSquares)
{
    function.open("images/function.dat");
    polynomialInterp.open("images/polynomialInterp.dat");
    cubicSpline.open("images/cubicSpline.dat");
    leastSquares.open("images/leastSquares.dat");
    trigInterp.open("images/trigInterp.dat");
    trigLeastSquares.open("images/trigLeastSquares.dat");

    if(!function.is_open()) {
        std::cout << "Could not open file 'function.dat', make sure the images folder exists" << std::endl;
        return false;
    }

    return true;
}

bool closeFiles(std::ofstream &function, std::ofstream &polynomialInterp, std::ofstream &cubicSpline, std::ofstream &leastSquares, std::ofstream &trigInterp, std::ofstream &trigLeastSquares)
{
    function.close();
    polynomialInterp.close();
    cubicSpline.close();
    leastSquares.close();
    trigInterp.close();
    trigLeastSquares.close();
}


int main (void) {
    const int length = 21;
    double x_i[length], y_i[length];
    fillFArrays(x_i, y_i, length);

    std::ofstream function, polynomialInterp, cubicSpline, leastSquares, trigInterp, trigLeastSquares;
    if (!openFiles(function, polynomialInterp, cubicSpline, leastSquares, trigInterp, trigLeastSquares)) {
        return 1;
    }

    // SETUP INTERPOLANTS

    // allocate polynomial interpolant
    gsl_spline *interp_poly = gsl_spline_alloc(gsl_interp_polynomial, length);
    // allocate natural cubic spline interpolant
    gsl_spline *interp_cspline = gsl_spline_alloc(gsl_interp_cspline, length);

    // initialize interpolants
    gsl_spline_init(interp_poly, x_i, y_i, length);
    gsl_spline_init(interp_cspline, x_i, y_i, length);

    // WRITE POINTS TO FILES

    // mark following points with a plus
    function         << "#m=0,S=2\n";
    polynomialInterp << "#m=0,S=2\n";
    cubicSpline      << "#m=0,S=2\n";
    for (int i = 0; i < length; i++) {
        function         << x_i[i] << " " << y_i[i] << "\n";
        polynomialInterp << x_i[i] << " " << y_i[i] << std::endl;
        cubicSpline      << x_i[i] << " " << y_i[i] << std::endl;
    }

    // connect the following points with a line
    polynomialInterp << "#m=1,S=0\n";
    cubicSpline      << "#m=1,S=0\n";

    double interpValue;
    gsl_interp_accel *acc = gsl_interp_accel_alloc();
    for (double x = x_i[0]; x < x_i[length - 1]; x += 0.001) {
        interpValue = gsl_spline_eval(interp_poly, x, acc);
        polynomialInterp << x << " " << interpValue << "\n";

        interpValue = gsl_spline_eval(interp_cspline, x, acc);
        cubicSpline << x << " " << interpValue << "\n";
    }

    // free the memory and close the files
    gsl_interp_accel_free(acc);
    gsl_spline_free(interp_poly);
    gsl_spline_free(interp_cspline);
    closeFiles(function, polynomialInterp, cubicSpline, leastSquares, trigInterp, trigLeastSquares);

    // create the images with the gsl plotutils graph application
    system("./createImages.sh");
    return 0;
}
