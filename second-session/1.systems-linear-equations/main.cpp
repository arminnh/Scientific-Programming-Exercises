#include <fstream>
#include <iostream>
#include <gsl/gsl_vector_double.h>
#include <gsl/gsl_matrix_double.h>
#include <gsl/gsl_math.h>
#include <cmath>
#include <iomanip>

#include "functions.h"

// formula: sum_{j=1}^{n} ((1+i)^(j-1)) * x_j   =   ((1+i)^n - 1) / i

double formulaLeft(double i, double j)
{
    return pow(1+i, j-1);
}

double formulaRight(double i, int n)
{
    return (pow(1+i, n) - 1) / i;
}


double checkValuesInFormula(double i, int n)
{
    double leftSide = 0, rightSide = 0;
    //i *= drand48()*100;

    for (int j = 1; j <= n; j++) {
        leftSide += formulaLeft(i, j);
    }
    rightSide = formulaRight(i, n);

    std::cout << "i = "           <<  std::setw(5) << std::setprecision(3) << i << ", n = " << n
              << ", left side:  " << std::setw(10) << std::setprecision(5) << leftSide
              << ", right side: " << std::setw(10) << std::setprecision(5) << rightSide << std::endl;
}


void fillSystem(gsl_matrix* A, gsl_vector *Y, int n)
{
    for (size_t row = 0; row < n; ++row) {
        for (size_t col = 0; col < n; ++col) {
            gsl_matrix_set(A, row, col, formulaLeft(row+1, col+1));
        }
        gsl_vector_set(Y, row, formulaRight(row+1, n));
        //checkValuesInFormula(row+1, n);
    }
}


int main (void)
{
    //Open the file to write output to
    std::ofstream output("output.txt", std::ofstream::out);

    for (int n = 10; n <= 15; n++) {
        //Initialize matrices A and Y for the equation Ax = Y
        gsl_matrix *A = gsl_matrix_alloc(n, n);
        gsl_vector *Y = gsl_vector_alloc(n);

        //Put the input data into matrix A and vector Y
        fillSystem(A, Y, n);

        //Do the exercise for the input data
        solve(A, Y, output);

        //Free the memory
        gsl_matrix_free(A);
        gsl_vector_free(Y);

        output   <<  "\n===============================\n" << std::endl;
        std::cout << "\n===============================\n" << std::endl;
    }

    //Free the memory
    output.close();
    return 0;
}
