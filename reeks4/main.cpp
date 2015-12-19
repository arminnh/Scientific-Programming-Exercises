#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <gsl/gsl_sf_trig.h>

void printArray(const double *x, const int m) {
    for (int i = 0; i < m; i++) {
        std::cout << x[i];
        if (i != m-1) std::cout << ", ";
        else std::cout << std::endl;
    }
}

double fx(double x) {
    //return (x > 0) ? x : -x;
    return sqrt( 1 + (x/5.0) );
}

double calcCoeff(double *t, double *x, bool a, int j, int m) {
    double result = 0;

    for (int k = 0; k < m; k++) {
        result += x[k] * ((a) ? gsl_sf_cos(j * t[k]) : gsl_sf_sin(j * t[k]));
    }

    result *= 2.0/(double) m;
    return result;
}

void solveForN(int n, double *t, double *x, int m, std::ofstream &out) {
    double coeff[2 * n + 1];
    coeff[0] = calcCoeff(t, x, true, 0, m)/2;

    //Generate coefficients
    for (int i = 0; i < n; i++) {
        int j = 2*i+1;
        coeff[j] = calcCoeff(t, x, true, i+1, m);
        coeff[j+1] = calcCoeff(t, x, false, i+1, m);

        if (i == n-1 and n == m/2) {
            coeff[j] /= 2;
        }
    }

    //Print out the  approximation function
    std::cout << "f(x) = " << coeff[0] << " + " ;
    for (int i = 0; i < n; i++) {
        int j = 2*i+1;
        std::cout << coeff[j] << "*cos(" << i+1 << "x) + ";
        std::cout << coeff[j+1] << "*sin(" << i+1 << "x)";
        std::cout << ((i != n-1) ? " + " : "\n");
    }

    //Generate approximated values
    for (double xx = -M_PI; xx < M_PI; xx = xx + 0.01) {
        double y = coeff[0];
        for (int i = 0; i < n; i++) {
            int j = 2*i+1;
            y += coeff[j]   * gsl_sf_cos((i+1)*xx);
            y += coeff[j+1] * gsl_sf_sin((i+1)*xx);
        }

        out << xx << " " << y << std::endl;
    }

}

void doExercise(int const m, int n) {
    //t = equidistant points, x = f(t)
    double t[m], x[m];

    std::stringstream mm, nn;
    mm << m;  nn << n;
    std::ofstream out;
    out.open("images/m" + mm.str() + "n" + nn.str() + ".dat");
    out << "#m=0,S=2\n";
    for (int i = 1; i <= m; i++) {
        t[i-1] = -1 + (2*(i-1) / (double) (m-1));
        x[i-1] = fx(t[i-1]);
        t[i-1] = M_PI * t[i-1];
        out << t[i-1]  << " "  << x[i-1] << std::endl;
    }

    std::cout << "m = " << m << " equidistant points as time values in [-1, 1] rescaled to [-pi,pi]: \n\t";
    printArray(t, m);

    out << "\n#m=1,S=0\n";
    for (double xx = -M_PI; xx < M_PI; xx = xx + 0.01) {
        out << xx << " " << fx(xx / M_PI) << std::endl;
    }

    out << "#m=1,S=0\n";
    std::cout << "n = " << n << " approximation: \n\t";
    solveForN(n, t, x, m, out);
    std::cout <<  std::endl;

    out.close();
}

int main (int argc, char *argv[]) {
    std::ofstream fxx;
    fxx.open("images/fx.dat");
    for (double xx = -M_PI; xx < M_PI; xx = xx + 0.01) {
        fxx << xx << " " << fx(xx) << std::endl;
    }

    doExercise(3, 1);
    doExercise(5, 1);
    doExercise(10, 1);
    doExercise(25, 1);
    doExercise(3, 3);
    doExercise(5, 3);
    doExercise(10, 3);
    doExercise(25, 3);

    fxx.close();
    system("./function_approximation.sh");
    return 0;
}
