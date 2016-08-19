#ifndef PROJECT_FUNCTIONS_H
#define PROJECT_FUNCTIONS_H

#include <fstream>
#include <gsl/gsl_vector_double.h>
#include <gsl/gsl_matrix_double.h>

void printVector(const gsl_vector *, std::string);
void printVector(const gsl_vector *, std::string, std::ostream &);
void printVectorCoutAndFile(const gsl_vector *, std::string, std::ostream &);
void printMatrix(const gsl_matrix *, std::string);
void printMatrix(const gsl_matrix *, std::string, std::ostream &);
void printMatrixCoutAndFile(const gsl_matrix *, std::string, std::ostream &);

void fillFArrays(double *x_i, double *y_i, int n);
void polynomialAndSplineSolutions(int m, double *x_i, double *y_i);
void leastSquaresSolutions(int m, int n, double *x_i, double a, double b, double *y_i, bool rescale=false);

double minArray(double *array, int n);
double maxArray(double *array, int n);

#endif //PROJECT_FUNCTIONS_H
