#include "./functions.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <gsl/gsl_linalg.h>
#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_deriv.h>
#include <gsl/gsl_spline.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <gsl/gsl_sf_log.h>
#include <gsl/gsl_linalg.h>

const int PRINT_WIDTH = 13;
const int PRINT_PRECISION = 5;

void printVector(const gsl_vector * v, std::string string) {
    std::cout << "Vector " << string << ":\n";
    for (unsigned int i = 0; i < v->size; i++) {
        std::cout << std::setw(PRINT_WIDTH) << std::setprecision(PRINT_PRECISION) << gsl_vector_get(v, i) << "\n";
    }
    std::cout << "\n";
}

void printVector(const gsl_vector * v, std::string string, std::ostream &out) {
    out << "Vector " << string << ":\n";
    for (unsigned int i = 0; i < v->size; i++) {
        out << std::setw(PRINT_WIDTH) << std::setprecision(PRINT_PRECISION) << gsl_vector_get(v, i) << "\n";
    }
    out << "\n";
}

void printVectorCoutAndFile(const gsl_vector * v, std::string string, std::ostream &out) {
    std::cout << "Vector " << string << ":\n";
    out << "Vector " << string << ":\n";
    for (unsigned int i = 0; i < v->size; i++) {
        std::cout << std::setw(PRINT_WIDTH) << std::setprecision(PRINT_PRECISION) << gsl_vector_get(v, i) << "\n";
        out << std::setw(PRINT_WIDTH) << std::setprecision(PRINT_PRECISION) << gsl_vector_get(v, i) << "\n";
    }
    std::cout << "\n";
    out << "\n";
}

void printMatrix(const gsl_matrix *m, std::string string) {
    std::cout << "Matrix " << string << ":\n";

    for (unsigned int i = 0; i < m->size1; i++) {
        for (unsigned int j = 0; j < m->size2; j++) {
            std::cout << std::setw(PRINT_WIDTH) << std::setprecision(PRINT_PRECISION) << gsl_matrix_get(m, i, j);
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void printMatrix(const gsl_matrix *m, std::string string, std::ostream &out) {
    out << "Matrix " << string << ":\n";
    for (unsigned int i = 0; i < m->size1; i++) {
        for (unsigned int j = 0; j < m->size2; j++) {
            out << std::setw(PRINT_WIDTH) << std::setprecision(PRINT_PRECISION) << gsl_matrix_get(m, i, j);
        }
        out << "\n";
    }
    out << "\n";
}

void printMatrixCoutAndFile(const gsl_matrix *m, std::string string, std::ostream &out) {
    std::cout << "Matrix " << string << ":\n";
    out << "Matrix " << string << ":\n";
    for (unsigned int i = 0; i < m->size1; i++) {
        for (unsigned int j = 0; j < m->size2; j++) {
            std::cout << std::setw(PRINT_WIDTH) << std::setprecision(PRINT_PRECISION) << gsl_matrix_get(m, i, j);
            out << std::setw(PRINT_WIDTH) << std::setprecision(PRINT_PRECISION) << gsl_matrix_get(m, i, j);
        }
        std::cout << "\n";
        out << "\n";
    }
    std::cout << "\n";
    out << "\n";
}

int f(int i)
{
    return (int) pow(-1, i);
}

void fillFArrays(double *x_i, double *y_i, int n)
{
    for (int i = 0; i < n; i++) {
        x_i[i] = i - 10;
        y_i[i] = f(i - 10);
    }
}

bool openFiles(std::ofstream &polynomialInterp, std::ofstream &cubicSpline, std::ofstream &leastSquares, std::ofstream &trigInterp, std::ofstream &trigLeastSquares)
{
    polynomialInterp.open("images/polynomialInterp.dat");
    cubicSpline.open("images/cubicSpline.dat");
    leastSquares.open("images/leastSquares.dat");
    trigInterp.open("images/trigInterp.dat");
    trigLeastSquares.open("images/trigLeastSquares.dat");

    return true;
}

bool closeFiles(std::ofstream &polynomialInterp, std::ofstream &cubicSpline, std::ofstream &leastSquares, std::ofstream &trigInterp, std::ofstream &trigLeastSquares)
{
    polynomialInterp.close();
    cubicSpline.close();
    leastSquares.close();
    trigInterp.close();
    trigLeastSquares.close();
}

void polynomialAndSplineSolutions(int m, double *x_i, double *y_i)
{
    std::ofstream polynomialInterp, cubicSpline, leastSquares, trigInterp, trigLeastSquares;
    if (!openFiles(polynomialInterp, cubicSpline, leastSquares, trigInterp, trigLeastSquares)) {
        return;
    }

    // SETUP INTERPOLANTS

    // allocate polynomial interpolant
    gsl_spline *interp_poly = gsl_spline_alloc(gsl_interp_polynomial, m);
    // allocate natural cubic spline interpolant
    gsl_spline *interp_cspline = gsl_spline_alloc(gsl_interp_cspline, m);

    // initialize interpolants
    gsl_spline_init(interp_poly, x_i, y_i, m);
    gsl_spline_init(interp_cspline, x_i, y_i, m);

    // WRITE POINTS TO FILES

    // mark following points with a plus
    polynomialInterp << "#m=0,S=2\n";
    cubicSpline      << "#m=0,S=2\n";
    for (int i = 0; i < m; i++) {
        polynomialInterp << x_i[i] << " " << y_i[i] << std::endl;
        cubicSpline      << x_i[i] << " " << y_i[i] << std::endl;
    }

    // connect the following points with a line
    polynomialInterp << "#m=1,S=0\n";
    cubicSpline      << "#m=1,S=0\n";

    double interpValue;
    gsl_interp_accel *acc = gsl_interp_accel_alloc();
    for (double x = x_i[0]; x < x_i[m - 1]; x += 0.001) {
        interpValue = gsl_spline_eval(interp_poly, x, acc);
        polynomialInterp << x << " " << interpValue << "\n";

        interpValue = gsl_spline_eval(interp_cspline, x, acc);
        cubicSpline << x << " " << interpValue << "\n";
    }

    // free the memory and close the files
    gsl_interp_accel_free(acc);
    gsl_spline_free(interp_poly);
    gsl_spline_free(interp_cspline);
    closeFiles(polynomialInterp, cubicSpline, leastSquares, trigInterp, trigLeastSquares);
}

// solve overdetermined matrix where m = amount of points, n = amount of unknowns, x_i = array of x values in [a, b], y_i = array of y values
void leastSquaresSolutions(int m, int n, double *x_input, double a, double b, double *y_i, bool rescale)
{
    std::stringstream ss; ss << n;
    std::string scale = "";

    double x_i[m];
    // rescale the x values we will work with
    for (int i = 0; i < m; i++) {
        if (rescale) {
            x_i[i] = ((1 - -1) * (x_input[i] - a) / (b - a)) - 1;
        } else {
            x_i[i] = x_input[i];
        }
    }

    if (rescale) {
        a = -1;
        b = 1;
        scale = "_rescaled";
    }

    // files to write data points for graphs to
    std::ofstream output, gx;
    output.open("output/output_degree" + ss.str() + scale + ".txt");
    gx.open("images/leastSquares" + ss.str() +  scale + ".dat");

    if (!output.is_open()) {
        std::cout << "Could not open file 'output.dat', make sure the output folder exists" << std::endl;
        return;
    }

    if (!gx.is_open()) {
        std::cout << "Could not open file 'gx_degree" + ss.str() +  scale + ".dat', make sure the images folder exists" << std::endl;
        return;
    }

    // initialize matrices A and Y for the equation A lamda = Y
    gsl_matrix *A = gsl_matrix_alloc(m, n);
    gsl_vector *Y = gsl_vector_alloc(m);

    // put the input data into matrix A and vector Y
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            gsl_matrix_set(A, i, j, gsl_pow_int(x_i[i], j));
        }
        gsl_vector_set(Y, i, y_i[i]);
    }

    // initialize work matrices and vectors
    gsl_matrix *QR = gsl_matrix_alloc(m, n),
               *U = gsl_matrix_alloc(m, n),
               *V = gsl_matrix_alloc(n, n);
    gsl_vector *tau = gsl_vector_alloc(n),
               *X = gsl_vector_alloc(n),
               *R = gsl_vector_alloc(m),
               *S = gsl_vector_alloc(n),
               *work = gsl_vector_alloc(n);

    gsl_matrix_memcpy(QR, A);
    gsl_matrix_memcpy(U, A);

    gsl_linalg_QR_decomp(QR, tau);
    gsl_linalg_QR_lssolve(QR, tau, Y, X, R);

    printMatrix(A, "input A", output);
    printVector(Y, "input Y", output);
    printMatrix(QR, "QR, received by QR decomposition", output);
    printVector(X, "X, solution found by solving after QR decomposition", output);
    printVector(R, "residual R = y - Ax", output);

    // mark the following points on the graph with a plus sign
    gx << "#m=0,S=3\n";

    // output given data points to files
    for (int i = 0; i < m; i++) {
        gx << x_i[i] << " " << y_i[i] << std::endl;
    }

    // connect the following data points with a line
    gx << "#m=1,S=0\n";

    // calculate new values for the graphs
    for (double x = a; x <= b; x = x + 0.01) {
        double y = gsl_vector_get(X, n-1);
        // use horners method to calculate the y values
        for (int i = n-1; i > 0; i--) {
            y = y*x + gsl_vector_get(X, i-1);
        }

        gx << x << " " << y << std::endl;
    }

    // the condition number we will use is max(S) / min(S)
    //gsl_linalg_SV_decomp(U, V, S, work);
    //double condNumber, minS, maxS;
    //minS = gsl_vector_get(S, 0);
    //maxS = gsl_vector_get(S, 0);
    //for (int j = 0; j < n; j++) {
    //    if (gsl_vector_get(S, j) < minS) minS = gsl_vector_get(S, j);
    //    if (gsl_vector_get(S, j) > maxS) maxS = gsl_vector_get(S, j);
    //}
    //condNumber = fabs(maxS) / fabs(minS);
    //output << "Calculating condition number by: abs(max(singular values)) / abs(min(singular values)):\n\t";
    //output << "Condition number: " << condNumber << std::endl;

    // free the memory and close the files
    gsl_matrix_free(A);
    gsl_matrix_free(QR);
    gsl_matrix_free(U);
    gsl_matrix_free(V);
    gsl_vector_free(Y);
    gsl_vector_free(tau);
    gsl_vector_free(X);
    gsl_vector_free(R);
    gsl_vector_free(S);
    gsl_vector_free(work);
    output.close();
    gx.close();
}

double minArray(double *array, int n)
{
    size_t i;
    double minimum = array[0];
    for (i = 1; i < n; ++i) {
        if (minimum > array[i]) {
            minimum = array[i];
        }
    }
    return minimum;
}

double maxArray(double *array, int n)
{
    size_t i;
    double maximum = array[0];
    for (i = 1; i < n; ++i) {
        if (maximum < array[i]) {
            maximum = array[i];
        }
    }
    return maximum;
}
