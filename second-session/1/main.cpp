#include <fstream>
#include <iostream>
#include <gsl/gsl_vector_double.h>
#include <gsl/gsl_matrix_double.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>

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

void fillA(gsl_matrix* A, int i)
{
    for (size_t r = 0; r < A->size1; ++r) {
        for (size_t j = 0; j < A->size2; ++j) {
            gsl_matrix_set(A, r, j, formulaLeft(i, j));
        }
    }
}

void fillY(gsl_vector* Y, int i)
{
    int n = 10;
    for (size_t r = 0; r < Y->size; ++r) {
        gsl_vector_set(Y, r, formulaRight(i, n));
        n++;
    }
}

void fillSystem(gsl_matrix* A, gsl_vector *Y, int n)
{

}



int main (void)
{
    static const int size_i = 6, size_j = 15;

    //Open the file to write output to
    std::ofstream output("output.txt", std::ofstream::out);

    //Initialize matrices A and Y for the equation Ax = Y
    gsl_matrix *A = gsl_matrix_alloc(size_i, size_j);
    gsl_vector *Y = gsl_vector_alloc(size_i);

    //Put the input data into matrix A and vector Y
    for (int n = 10; n < 16; n++) {
        //fillSystem(A, Y, n);
    }
    fillSystem(A, Y, 15);
    printMatrix(A, "A");
    printVector(Y, "Y");

    //Do the exercise for the input data
    //solve(A, Y, output);

    output   <<  "\n===============================\n" << std::endl;
    std::cout << "\n===============================\n" << std::endl;

    //Free the memory
    output.close();
    gsl_matrix_free(A);
    gsl_vector_free(Y);

    return 0;
}
