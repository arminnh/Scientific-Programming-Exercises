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

void printArray(const double *x, const int m);
double minArray(double *array, int n);
double maxArray(double *array, int n);

void writeDataPoints(double *x_i, double *y_i, int m);
void fillFArrays(double *x_i, double *y_i, int m);
void polynomialAndSplineSolutions(int m, double *x_i, double *y_i);
void leastSquaresApproximation(int m, int n, double *x_i, double a, double b, double *y_i);
void trigonometricApproximation(int n, int m, double *x_i, double a, double b, double *y_i);

#endif //PROJECT_FUNCTIONS_H
