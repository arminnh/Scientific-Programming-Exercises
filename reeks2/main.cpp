#include <fstream>
#include <iostream>
#include <gsl/gsl_vector_double.h>
#include <gsl/gsl_matrix_double.h>

#include "functions.h"

int main (void) {
    static const int size_i = 3, size_j = 3;

    //Input data which will be used to create and solve systems of equations
    double a[][size_j] = {{3.021,  2.714, 6.913},
                          {1.031, -4.273, 1.121},
                          {5.084, -5.832, 9.155}};
    double y[] = {12.648,
                  -2.121,
                  8.407};

    //Open the file to write output to
    std::ofstream output("output.txt", std::ofstream::out);

    //Initialize matrices A and Y for the equation Ax = Y
    gsl_matrix *A = gsl_matrix_alloc(size_i, size_j);
    gsl_vector *Y = gsl_vector_alloc(size_j);

    //Put the input data into matrix A and vector Y
    for (int i = 0; i < size_i; i++) {
        for (int j = 0; j < size_j; j++) {
            gsl_matrix_set(A, i, j, a[i][j]);
        }
        gsl_vector_set(Y, i, y[i]);
    }

    //Do the exercise for the input data
    solve(A, Y, output);

    output   <<  "\n===============================\n" << std::endl;
    std::cout << "\n===============================\n" << std::endl;

    //Introduce a change into A
    output    << "Changed a_1,1 from " << gsl_matrix_get(A, 1, 1) <<" to -4.275" << std::endl;
    std::cout << "Changed a_1,1 from " << gsl_matrix_get(A, 1, 1) <<" to -4.275" << std::endl;
    gsl_matrix_set(A, 1, 1, -4.275);

    //Do the exercise for the changed matrix A
    solve(A, Y, output);

    //Free the memory
    output.close();
    gsl_matrix_free(A);
    gsl_vector_free(Y);

    return 0;
}
