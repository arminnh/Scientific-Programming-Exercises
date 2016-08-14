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


double checkValuesInFormula(int n, double i)
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
    //double i[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    //double i[15] = {1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 1.2, 1.3, 1.4, 1.5, 1.6};
    //double i[15] = {1.73, 2.13, 3.56, 4.43, 5.987, 6.34, 7.456, 8.23, 9.11, 10, 11, 12, 13, 14, 15};
    //double i[15] = {6.1, 3.2, 8.3, 5.4, 7.5, 4.6, 9.7, 2.8, 1.9, 10, 11, 12, 13, 14, 15};

    for (size_t row = 0; row < n; ++row) {
        for (size_t col = 0; col < n; ++col) {
            gsl_matrix_set(A, row, col, formulaLeft(row+1, col+1));
        }
        gsl_vector_set(Y, row, formulaRight(row+1, n));
        //checkValuesInFormula(n, i[r-1]);

        //double random_i = drand48()/100;
        //fillRowLeft(A, r-1, matrix_size, random_i);
        //fillRowRight(Y, r-1, matrix_size, random_i);
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
