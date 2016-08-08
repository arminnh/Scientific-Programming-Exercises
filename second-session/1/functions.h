#ifndef PROJECT_FUNCTIONS_H
#define PROJECT_FUNCTIONS_H

#include <fstream>
#include <gsl/gsl_vector_double.h>
#include <gsl/gsl_matrix_double.h>

void printVector(const gsl_vector * v, std::string string);
void printVector(const gsl_vector * v, std::string string, std::ostream &);
void printVectorCoutAndFile(const gsl_vector * v, std::string string, std::ostream &);
void printMatrix(const gsl_matrix *m, std::string string);
void printMatrix(const gsl_matrix *m, std::string string, std::ostream &);
void printMatrixCoutAndFile(const gsl_matrix *m, std::string string, std::ostream &);

void solve(gsl_matrix *A, gsl_vector *Y, std::ostream &);

#endif //PROJECT_FUNCTIONS_H
