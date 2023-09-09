#include "SecondOrderDynamics.h"

#include <iostream>

SecondOrderDynamics::SecondOrderDynamics(double f, double z, double r, double x0) {
    k1 = z / (3.14 * f);
    k2 = 1 / ((2 * 3.14 * f) * (2 * 3.14 * f));
    k3 = r * z / (2 * 3.14 * f);

    xp = x0;
    y = x0;
    yd = 0;
}

double SecondOrderDynamics::update(double x, double xd) {
    y = y + 1 * yd;
    yd = yd + 1 * (x + k3*xd - y - k1*yd) / k2;

    return y;
}

double SecondOrderDynamics::update(double x) {
    double xd = (x - xp);
    xp = x;

    return update(x, xd);
}