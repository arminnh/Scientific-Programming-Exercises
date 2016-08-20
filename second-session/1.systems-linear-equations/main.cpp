#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <gsl/gsl_vector_double.h>
#include <gsl/gsl_matrix_double.h>
#include <sstream>

#include "functions.h"

int main (void)
{
    for (int n = 10; n <= 15; n++) {
        // open the file to write output to
        std::stringstream ss; ss << n;
        std::ofstream output("output_n_" + ss.str() + ".txt", std::ofstream::out);

        // initialize matrices A and Y for the equation Ax = Y
        gsl_matrix *A = gsl_matrix_alloc(n, n);
        gsl_vector *Y = gsl_vector_alloc(n);

        // put the input data into matrix A and vector Y
        fillSystem(A, Y, n);

        // do the exercise for the input data
        solve(A, Y, output);

        gsl_matrix_set(A, 9, 1, 1);
        std::cout << "Changed input matrix cell (10, 2) to 1.\n\n";
        output << "Changed input matrix cell (10, 2) to 1.\n\n";
        solve(A, Y, output);

        // free the memory
        gsl_matrix_free(A);
        gsl_vector_free(Y);
        output.close();

        std::cout << "\n===============================\n" << std::endl;
    }
    return 0;
}
