#pragma once

#include <cmath>


static double square(const double x) {
    return x * x;
}

static double cube(const double x) {
    return x * x * x;
}

static double _pow(const double x, const double exponent) {
    return pow(x, exponent);
}

static double inverse(const double x) {
    return 1 / x;
}

static double _sin(const double x) {
    return sin(x);
}

static double _cos(const double x) {
    return cos(x);
}

static double _sqrt(const double x) {
    return sqrt(x);
}

static double test(const double x) {
    return log(x) + inverse(x);
}