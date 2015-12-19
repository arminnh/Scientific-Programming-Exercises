#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_deriv.h>
#include <gsl/gsl_spline.h>
#include <algorithm>
#include <fstream>
#include <iostream>

//The given Runge function
double runge_f(double x) {
    return 1 / (1 + 25 * gsl_pow_2(x));
}

//Struct from gsl's "cspline.c" to be able to change the conditions on the endpoints of the spline
typedef struct
{
    double * c;
    double * g;
    double * diag;
    double * offdiag;
} cspline_state_t;


int main (void) {
    int i = 0, size = 17;
    double xi, xa1[size], ya1[size], xa2[size], ya2[size];

    //Files to write data points for graphs to
    std::ofstream runge, poly1, poly2, spline1, spline2;
    std::ofstream diff1abs, diff1rel, diff2abs, diff2rel, diff3abs, diff3rel, diff4abs, diff4rel, truncError;
    runge.open("images/runge.dat");
    poly1.open("images/poly1.dat"); poly2.open("images/poly2.dat");
    spline1.open("images/spline1.dat"); spline2.open("images/spline2.dat");
    diff1abs.open("images/diff1abs.dat"); diff1rel.open("images/diff1rel.dat");
    diff2abs.open("images/diff2abs.dat"); diff2rel.open("images/diff2rel.dat");
    diff3abs.open("images/diff3abs.dat"); diff3rel.open("images/diff3rel.dat");
    diff4abs.open("images/diff4abs.dat"); diff4rel.open("images/diff4rel.dat");
    truncError.open("images/trunError.dat");

    if(!runge.is_open()) {
        std::cout << "Could not open file 'runge.dat', make sure the images folder exists" << std::endl;
        return 0;
    }

    //Mark the following points on the graph with a plus sign
    poly1 << "#m=0,S=2\n";
    poly2 << "#m=0,S=2\n";
    spline1 << "#m=0,S=2\n";
    spline2 << "#m=0,S=2\n";

    //17 equidistant points from -1 to 1
    for (xi = -1; xi <= 1; xi = xi + ( 2 / (double) 16)) {
        xa1[i] = xi;
        ya1[i] = runge_f(xi);
        poly1 << xi << " " << ya1[i] << std::endl;
        spline1 << xi << " " << ya1[i] << std::endl;
        spline2 << xi << " " << ya1[i] << std::endl;
        i++;
    }


    //17 non equidistant points from -1 to 1
    for (i = 0; i <= 16; i++) {
        xa2[i] = cos( ((double)i + 0.5) * (M_PI / 17) );
    }
    //The points have to be sorted for the evaluation function
    std::sort(xa2, xa2 + size);
    for (i = 0; i <= 16; i++) {
        ya2[i] = runge_f(xa2[i]);
        poly2 << xa2[i] << " " << ya2[i] << std::endl;
    }

    gsl_interp_accel *acc = gsl_interp_accel_alloc();
    //First polynomial for the equidistant points
    gsl_spline *interp_poly1 = gsl_spline_alloc(gsl_interp_polynomial, size);
    //Second polynomial for the non equidistant points
    gsl_spline *interp_poly2 = gsl_spline_alloc(gsl_interp_polynomial, size);
    //Natural cubic spline through the equidistant points
    gsl_spline *interp_cspline1 = gsl_spline_alloc(gsl_interp_cspline, size);
    //Cubic spline with modified requirements in the endpoints
    gsl_spline *interp_cspline2 = gsl_spline_alloc(gsl_interp_cspline, size);

    //Initialize the polynomials
    gsl_spline_init(interp_poly1, xa1, ya1, size);
    gsl_spline_init(interp_poly2, xa2, ya2, size);
    gsl_spline_init(interp_cspline1, xa1, ya1, size);
    gsl_spline_init(interp_cspline2, xa1, ya1, size);

    //Change the conditions on the endpoints of the second cspline
    cspline_state_t *state = (cspline_state_t *) interp_cspline2->interp->state;
    state->c[0] = (double) 925 / 4394;
    state->c[size - 1] = (double) 925 / 4394;

    //Points of the runge function
    for (xi = -1; xi < 1; xi += 0.001) {
        runge << xi << " " << runge_f(xi) << std::endl;
    }

    //Connect the following data points with a line
    poly1 << "#m=1,S=0\n";
    poly2 << "#m=1,S=0\n";
    spline1 << "#m=1,S=0\n";
    spline2 << "#m=1,S=0\n";

    //Data points for the first interpolation polynomial and both of the csplines
    double interpValue, realValue;
    for (xi = xa1[0]; xi < xa1[16]; xi += 0.001) {
        interpValue = gsl_spline_eval(interp_poly1, xi, acc);
        realValue = runge_f(xi);
        poly1 << xi << " " << interpValue << std::endl;
        diff1abs << xi << " " << interpValue - realValue << std::endl;
        diff1rel << xi << " " << (interpValue - realValue) / realValue << std::endl;

        interpValue = gsl_spline_eval(interp_cspline1, xi, acc);
        spline1 << xi << " " << interpValue << std::endl;
        diff3abs << xi << " " << interpValue - realValue << std::endl;
        diff3rel << xi << " " << (interpValue - realValue) / realValue << std::endl;

        interpValue = gsl_spline_eval(interp_cspline2, xi, acc);
        spline2 << xi << " " << interpValue << std::endl;
        diff4abs << xi << " " << interpValue - realValue << std::endl;
        diff4rel << xi << " " << (interpValue - realValue) / realValue << std::endl;
    }

    //Data points for the second interpolation polynomial
    for (xi = xa2[0]; xi < xa2[16]; xi += 0.001) {
        interpValue = gsl_spline_eval(interp_poly2, xi, acc);
        realValue = runge_f(xi);
        poly2 << xi << " " << interpValue << std::endl;
        diff2abs << xi << " " << interpValue - realValue << std::endl;
        diff2rel << xi << " " << (interpValue - realValue) / realValue << std::endl;
    }

    //Free the memory and close the files
    gsl_interp_accel_free(acc);
    gsl_spline_free(interp_poly1);
    gsl_spline_free(interp_poly2);
    gsl_spline_free(interp_cspline1);
    gsl_spline_free(interp_cspline2);
    runge.close();
    poly1.close(); poly2.close();
    spline1.close(); spline2.close();
    diff1abs.close();diff1rel.close();
    diff2abs.close();diff2rel.close();
    diff3abs.close();diff3rel.close();
    diff4abs.close();diff4rel.close();
    truncError.close();

    //Create the images with the gsl graph application
    system("./createImages.sh");
    return 0;
}
