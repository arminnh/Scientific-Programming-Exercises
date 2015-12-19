#include <iostream>
#include <random>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_math.h>

//Calculate the area of the figure using n points
//smallerRectangle toggles which rectangle is used for the calculation
double calculateArea(int n, bool smallerRectangle) {
    std::random_device rd;
    //Use the ranlxs0 random number generator
    gsl_rng *r = gsl_rng_alloc(gsl_rng_ranlxs0);
    //Seed the generator with a random number
    gsl_rng_set(r, rd());

    double result = 0, x = 0, y = 0;
    for (int i = 0; i < n; i++) {
        // rescale the points with: x' = (b - a) x + a
        if (!smallerRectangle) {
            // 1 <= x <= 3 ,  -1 <= y <= 4
            x = 2 * gsl_rng_uniform (r) + 1;
            y = 5 * gsl_rng_uniform (r) - 1;
        } else {
            // 1 <= x <= 1.59374 ,  0.71828 <= y <= 3.03659
            x = 0.59374 * gsl_rng_uniform(r) + 1;
            y = 2.347618 * gsl_rng_uniform(r) + 0.718282;
        }

        if ((gsl_pow_int(x, 3) + gsl_pow_int(y, 3) <= 29) and (y >= exp(x) - 2)) result++;
    }
    if (!smallerRectangle) result *= 2.0 * 5.0 / n;
    else                result *= 0.59374 * 2.347618 / n;

    gsl_rng_free(r);
    return result;
}

//Calculate the area of the figure with an increasing n until the difference between 2 sequential areas <= e
//smallerRectangle toggles which rectangle is used for the calculation
double calculateUntil(double e, bool smallerRectangle) {
    std::random_device rd;
    //Use the ranlxs0 random number generator
    gsl_rng *r = gsl_rng_alloc(gsl_rng_ranlxs0);
    //Seed the generator with a random number
    gsl_rng_set(r, rd());
    //Chose a random n_0 ranging from 2000 to 5000
    int n = (int) (3000 * gsl_rng_uniform (r) + 2000);

    double result = calculateArea(n, smallerRectangle);
    double nextResult = calculateArea(n * 2, smallerRectangle);

    while (fabs(result - nextResult) > e) {
        n *= 2;
        result = nextResult;
        nextResult = calculateArea(n, smallerRectangle);
    }
    std::cout << "Area: " << result  << ", Number of points: " << n << std::endl;
    return result;
}

//Calculate the area of the figure n times using calculateUntil, then print the average
//smallerRectangle toggles which rectangle is used for the calculation
void calcAvgOfN(int n, double e, bool smallerRectangle) {
    double avgArea = 0;
    std::cout << "Calculating area using " << (smallerRectangle ? "a smaller" : "the given") << " rectangle" << std::endl;
    for (int i = 0; i < n; i++) {
        avgArea += calculateUntil(e, smallerRectangle);
    }
    avgArea /= n;
    std::cout << "Average Area: " << avgArea << std::endl << std::endl;
}



int main (int argc, char *argv[]) {
    calcAvgOfN(15, 0.01, true);
    calcAvgOfN(15, 0.01, false);

    return 0;
}