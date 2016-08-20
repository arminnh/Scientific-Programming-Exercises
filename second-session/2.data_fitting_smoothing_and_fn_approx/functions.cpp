#include "./functions.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_spline.h>
#include <algorithm>
#include <sstream>
#include <gsl/gsl_sf_trig.h>

const int PRINT_WIDTH = 13;
const int PRINT_PRECISION = 5;

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

void printArray(const double *x, const int m) {
    for (int i = 0; i < m; i++) {
        std::cout << x[i];
        if (i != m-1) std::cout << ", ";
        else std::cout << std::endl;
    }
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

int f(double i)
{
    return (int) pow(-1, i);
}

// write given points to dataPoints.dat
void writeDataPoints(double *x_i, double *y_i, int m)
{
    std::ofstream dataPoints;
    dataPoints.open("images/dataPoints.dat");

    if(!dataPoints.is_open()) {
        std::cerr << "Could not open file 'dataPoints.dat', make sure the images folder exists" << std::endl;
        return;
    }

    dataPoints << "#m=0,S=3\n";
    for (int i = 0; i < m; i++) {
        dataPoints << x_i[i] << " " << y_i[i] << "\n";
    }

    dataPoints.close();
}

void fillFArrays(double *x_i, double *y_i, int n)
{
    for (int i = 0; i < n; i++) {
        x_i[i] = i - 10;
        y_i[i] = f(i - 10);
    }
}

void polynomialAndSplineSolutions(int m, double *x_i, double *y_i)
{
    std::ofstream polynomialInterp, cubicSplineNatural, cubicSplinePeriodic;
    polynomialInterp.open("images/polynomialInterp.dat");
    cubicSplineNatural.open("images/cubicSplineNatural.dat");
    cubicSplinePeriodic.open("images/cubicSplinePeriodic.dat");

    if (!polynomialInterp.is_open()) {
        return;
    }

    // SETUP INTERPOLANTS

    // allocate polynomial interpolant
    gsl_spline *interp_poly = gsl_spline_alloc(gsl_interp_polynomial, m);
    // allocate natural cubic spline interpolant
    gsl_spline *interp_cspline_n = gsl_spline_alloc(gsl_interp_cspline, m);
    gsl_spline *interp_cspline_p = gsl_spline_alloc(gsl_interp_cspline_periodic, m);

    // initialize interpolants
    gsl_spline_init(interp_poly, x_i, y_i, m);
    gsl_spline_init(interp_cspline_n, x_i, y_i, m);
    gsl_spline_init(interp_cspline_p, x_i, y_i, m);

    // WRITE POINTS TO FILES

    // mark following points with a plus
    polynomialInterp    << "#m=0,S=3\n";
    cubicSplineNatural  << "#m=0,S=3\n";
    cubicSplinePeriodic << "#m=0,S=3\n";
    for (int i = 0; i < m; i++) {
        polynomialInterp    << x_i[i] << " " << y_i[i] << std::endl;
        cubicSplineNatural  << x_i[i] << " " << y_i[i] << std::endl;
        cubicSplinePeriodic << x_i[i] << " " << y_i[i] << std::endl;
    }

    // connect the following points with a line
    polynomialInterp    << "#m=1,S=0\n";
    cubicSplineNatural  << "#m=1,S=0\n";
    cubicSplinePeriodic << "#m=1,S=0\n";

    double interpValue;
    gsl_interp_accel *acc = gsl_interp_accel_alloc();
    for (double x = minArray(x_i, m); x <= maxArray(x_i, m); x += 0.001) {
        interpValue = gsl_spline_eval(interp_poly, x, acc);
        polynomialInterp << x << " " << interpValue << "\n";

        interpValue = gsl_spline_eval(interp_cspline_n, x, acc);
        cubicSplineNatural << x << " " << interpValue << "\n";

        interpValue = gsl_spline_eval(interp_cspline_p, x, acc);
        cubicSplinePeriodic << x << " " << interpValue << "\n";
    }

    // free the memory and close the files
    gsl_interp_accel_free(acc);
    gsl_spline_free(interp_poly);
    gsl_spline_free(interp_cspline_n);
    gsl_spline_free(interp_cspline_p);
    polynomialInterp.close();
    cubicSplineNatural.close();
    cubicSplinePeriodic.close();
}

// solve overdetermined matrix where m = amount of points, n = amount of unknowns, x_i = array of x values in [a, b], y_i = array of y values
void leastSquaresApproximation(int m, int n, double *x_i, double a, double b, double *y_i)
{
    std::stringstream ss; ss << n;

    double x_rescaled[m];
    // rescale the x values we will work with from [a, b] to [-1, 1]
    for (int i = 0; i < m; i++) {
        x_rescaled[i] = ((1 - -1) * (x_i[i] - a) / (b - a)) - 1;
    }
    a = -1;
    b = 1;

    // files to write data points for graphs to
    std::ofstream output, approximation;
    output.open("output/leastSquares_degree_" + ss.str() + ".txt");
    approximation.open("images/leastSquares_degree_" + ss.str() + ".dat");

    if (!output.is_open()) {
        std::cout << "Could not open file 'leastSquares_degree_.txt', make sure the output folder exists" << std::endl;
        return;
    }

    if (!approximation.is_open()) {
        std::cout << "Could not open file 'leastSquares_degree_" + ss.str() + ".dat', make sure the images folder exists" << std::endl;
        return;
    }

    // initialize matrices A and Y for the equation A lamda = Y
    gsl_matrix *A = gsl_matrix_alloc(m, n);
    gsl_vector *Y = gsl_vector_alloc(m);

    // put the input data into matrix A and vector Y
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            gsl_matrix_set(A, i, j, gsl_pow_int(x_rescaled[i], j));
        }
        gsl_vector_set(Y, i, y_i[i]);
    }

    // initialize work matrices and vectors
    gsl_vector *tau = gsl_vector_alloc(n),
               *X = gsl_vector_alloc(n),
               *R = gsl_vector_alloc(m),
               *S = gsl_vector_alloc(n),
               *work = gsl_vector_alloc(n);
    gsl_matrix *QR = gsl_matrix_alloc(m, n),
               *U = gsl_matrix_alloc(m, n),
               *V = gsl_matrix_alloc(n, n);

    gsl_matrix_memcpy(QR, A);
    gsl_matrix_memcpy(U, A);

    gsl_linalg_QR_decomp(QR, tau);
    gsl_linalg_QR_lssolve(QR, tau, Y, X, R);

    printMatrix(A, "input A", output);
    printVector(Y, "input Y", output);
    printMatrix(QR, "QR, received by QR decomposition", output);
    printVector(X, "X, solution found by solving after QR decomposition", output);
    printVector(R, "residual R = y - Ax", output);

    // add following invisible points for better automatic graph generation
    approximation << "#m=0,S=0\n";
    approximation << 1.1  << " " << 1.1;
    approximation << 1.1  << " " << -1.1;
    approximation << -1.1 << " " << 1.1;
    approximation << -1.1 << " " << -1.1;

    // mark the following points on the graph with a plus sign
    approximation << "#m=0,S=3\n";

    // output given data points to files
    for (int i = 0; i < m; i++) {
        approximation << x_rescaled[i] << " " << y_i[i] << std::endl;
    }

    // connect the following data points with a line
    approximation << "#m=1,S=0\n";

    // calculate new values for the graphs
    for (double x = a; x <= b + 0.001; x = x + 0.001) {
        double y = gsl_vector_get(X, n-1);
        // use horners method to calculate the y values
        for (int i = n-1; i > 0; i--) {
            y = y*x + gsl_vector_get(X, i-1);
        }

        approximation << x << " " << y << std::endl;
    }

    // the condition number we will use is max(S) / min(S)
    gsl_linalg_SV_decomp(U, V, S, work);
    double condNumber, minS, maxS;
    minS = gsl_vector_get(S, 0);
    maxS = gsl_vector_get(S, 0);
    for (int j = 0; j < n; j++) {
        if (gsl_vector_get(S, j) < minS) minS = gsl_vector_get(S, j);
        if (gsl_vector_get(S, j) > maxS) maxS = gsl_vector_get(S, j);
    }
    condNumber = fabs(maxS) / fabs(minS);
    output << "Calculating condition number by: abs(max(singular values)) / abs(min(singular values)):\n\t";
    output << "Condition number: " << condNumber << std::endl;

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
    approximation.close();
}

double fourierCoefficient(int j, int n, double *t_i, double *x_i, bool a) {
    double result = 0;

    for (int k = 0; k < n; k++) {
        result += x_i[k] * ((a) ? gsl_sf_cos(j * t_i[k]) : gsl_sf_sin(j * t_i[k]));
    }

    result *= 2.0/(double) n;
    return result;
}

void fourierSolve(int n, double *t_i, double *x_i, int m, std::ofstream &out) {
    double coeff[2 * m + 1];
    coeff[0] = fourierCoefficient(0, n, t_i, x_i, true) / 2;

    // generate coefficients
    for (int i = 1; i <= m; i++) {
        int j = 2 * i;
        coeff[j-1] = fourierCoefficient(i, n, t_i, x_i, true);
        coeff[j]   = fourierCoefficient(i, n, t_i, x_i, false);

        // if n == 2m, divide last a coefficient by 2. last b coefficient will be 0
        if (i == m and n == 2*m) {
            coeff[j]  /= 2;
            coeff[j+1] = 0;
        }
    }

    // print out the approximation function
    /*std::cout << "n = " << n << " approximation: \n\t";
    std::cout << "f(x) = " << coeff[0] << " + " ;
    for (int i = 1; i <= m; i++) {
        int j = 2 * i;
        std::cout << coeff[j-1] << "*cos(" << i << "x) + ";
        std::cout << coeff[j]   << "*sin(" << i << "x)";
        std::cout << ((i != m) ? " + " : "\n");
    }
    std::cout << std::endl;*/

    out << "#m=1,S=0\n";
    // generate approximated values
    for (double x = 0; x < 2*M_PI + 0.001; x = x + 0.001) {
        double y = coeff[0];
        for (int i = 1; i <= m; i++) {
            int j = 2 * i;
            y += coeff[j-1] * gsl_sf_cos(i * x);
            y += coeff[j]   * gsl_sf_sin(i * x);
        }

        out << x << " " << y << std::endl;
    }
}

// n given points, equidistant points t_i, corresponding data values x_i
void trigonometricApproximation(int n, int m, double *t_i, double a, double b, double *x_i) {
    std::stringstream mm, nn;
    mm << m;
    nn << n;

    std::ofstream out;
    out.open("images/trigApprox_n_" + nn.str() + "_m_" + mm.str() + ".dat");
    out << "#m=0,S=3\n";

    double t_rescaled[n];
    // rescaled value = (value - (old min)) * (new range)/(old range)) + (new min)
    // new min = 0
    double new_max;
    if (b - a > 2 * M_PI) {
        new_max = (n-1) * (2*M_PI / n);
    } else {
        new_max = 2*M_PI;
    }
    double range_multiplier = (new_max - 0) / (b - a); // (new range) / (old range)

    for (int i = 0; i < n; i++) {
        t_rescaled[i] = (t_i[i] - a) * range_multiplier;
        out << t_rescaled[i]  << " "  << x_i[i] << std::endl;
    }

    //std::cout << "n = " << n << " equidistant points as time values in [" << a << ", " << b << "] rescaled to [0 , 2pi]: \n\t";
    //printArray(t_rescaled, n);

    fourierSolve(n, t_rescaled, x_i, m, out);
    out.close();
}
