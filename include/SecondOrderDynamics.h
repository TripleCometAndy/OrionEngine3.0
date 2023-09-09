#pragma once

class SecondOrderDynamics {
private:
    double xp;
    double y;
    double yd;
    double k1;
    double k2;
    double k3;
public:
    SecondOrderDynamics(double f, double z, double r, double x0);
    double update(double x, double xd);
    double update(double x);
};