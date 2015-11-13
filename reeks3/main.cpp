#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_log.h>
#include <gsl/gsl_linalg.h>

void printVector(const gsl_vector * v, std::string string, std::ostream &out) {
    out << "Vector " << string << ":\n";
    for (unsigned int i = 0; i < v->size; i++) {
        out << std::setw(21) << std::setprecision(15) << gsl_vector_get(v, i) << "\n";
    }
    out << "\n";
}

void printMatrix(const gsl_matrix *m, std::string string, std::ostream &out) {
    out << "Matrix " << string << ":\n";
    for (unsigned int i = 0; i < m->size1; i++) {
        for (unsigned int j = 0; j < m->size2; j++) {
            out << std::setw(21) << std::setprecision(15) << gsl_matrix_get(m, i, j);
        }
        out << "\n";
    }
    out << "\n";
}

int main (int argc, char *argv[]) {
    if (argc < 2 or argc > 3) {
        std::cout << "Wrong amount of arguments given." << std::endl;
        std::cout << "\tUsage: " << argv[0] << " n: Creates an approximating model for the data points" << std::endl;
        std::cout << "\t       " << argv[0] << " n rescale: Creates an approximating model for the data points, after rescaling the x values" << std::endl;
        return -1;
    }
    std::stringstream ss(argv[1]);

    //size = amount of points given
    int const size = 7;

    int n;
    if (!(ss >> n) or (n > size)) {
        std::cerr << "Invalid number for degree n: " << argv[1] << std::endl;
        std::cerr << "n has to lie between 1 and 7" << std::endl;
        return -1;
    }

    /*  Input data points
     *         x | 0.635 1.435 2.235 3.035 3.835 4.635 5.435
     *  f(x) = y | 7.50  4.35  2.97  2.20  1.70  1.28  1.00
     */
    double xa1[size] = {0.635, 1.435, 2.235, 3.035, 3.835, 4.635, 5.435},
            ya1[size] = {7.50, 4.35, 2.97, 2.20, 1.70, 1.28, 1.00};

    //points for model g(x) for log(y(x))
    double ya2[size];

    std::string scale = "";
    //rescale the x values we will work with
    if (argc == 3) {
        for (int i = 0; i < size; i++) {
            xa1[i] = (2 * xa1[i] - 1.27) / 4.8 - 1;
        }
        scale = "_rescaled";
    }

    //Files to write data points for graphs to
    std::ofstream output, datapoints, log_datapoints, gx, exp_gx;
    output.open("output/output_degree" + ss.str() + scale + ".txt");
    datapoints.open("images/datapoints.dat");
    log_datapoints.open("images/log_datapoints.dat");
    gx.open("images/gx_degree" + ss.str() +  scale + ".dat");
    exp_gx.open("images/exp_gx_degree" + ss.str() +  scale + ".dat");

    if (!datapoints.is_open()) {
        std::cout << "Could not open file 'datapoints.dat', make sure the images folder exists" << std::endl;
        return 0;
    }

    //Mark the following points on the graph with a plus sign
    datapoints << "#m=0,S=3\n";
    log_datapoints << "#m=0,S=3\n";
    gx << "#m=0,S=3\n";
    exp_gx << "#m=0,S=3\n";

    //Output given data points to files
    for (int i = 0; i < size; i++) {
        datapoints << xa1[i] << " " << ya1[i] << std::endl;
        exp_gx     << xa1[i] << " " << ya1[i] << std::endl;

        ya2[i] = gsl_sf_log(ya1[i]);
        log_datapoints << xa1[i] << " " << ya2[i] << std::endl;
        gx             << xa1[i] << " " << ya2[i] << std::endl;
    }

    //Initialize matrices A and Y for the equation A lamda = Y
    gsl_matrix *A = gsl_matrix_alloc(size, n);
    gsl_vector *Y = gsl_vector_alloc(size);

    //Put the input data into matrix A and vector Y
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < n; j++) {
            gsl_matrix_set(A, i, j, gsl_pow_int(xa1[i], j));
        }
        gsl_vector_set(Y, i, ya2[i]);
    }

    gsl_vector *tau = gsl_vector_alloc(n),
               *X = gsl_vector_alloc(n),
               *R = gsl_vector_alloc(size),
               *S = gsl_vector_alloc(n),
               *work = gsl_vector_alloc(n);
    gsl_matrix *QR = gsl_matrix_alloc(size, n),
               *U = gsl_matrix_alloc(size, n),
               *V = gsl_matrix_alloc(n, n);
    gsl_matrix_memcpy(QR, A);
    gsl_matrix_memcpy(U, A);

    gsl_linalg_QR_decomp(QR, tau);
    gsl_linalg_QR_lssolve(QR, tau, Y, X, R);

    printMatrix(A, "input A", output);
    printVector(Y, "input Y", output);
    //printMatrix(QR, "QR, received by QR decomposition", output);
    printVector(X, "X, solution found by solving after QR decomposition", output);
    printVector(R, "residual R = y - Ax", output);

    //Connect the following data points with a line
    gx << "#m=1,S=0\n";
    exp_gx << "#m=1,S=0\n";

    //Write new data points to files
    double leftLimit = 0.5, rightLimit = 5.5;
    if (argc == 3) {
        leftLimit = -1;
        rightLimit = 1;
    }
    for (double x = leftLimit; x < rightLimit; x = x + 0.01) {
        double y = 0;
        for (int i = 0; i < n; i++) {
            y += gsl_vector_get(X, i) * gsl_pow_int(x, i);
        }
        gx     << x << " " << y      << std::endl;
        exp_gx << x << " " << exp(y) << std::endl;
    }

    //The condition number we will use is max(S) / min(S)
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

    //Free the memory and close the files
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
    datapoints.close();
    log_datapoints.close();
    gx.close();
    exp_gx.close();
    return 0;
}
