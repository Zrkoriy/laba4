#include "../include/methods.hpp"
#include <cmath>
#include <stdexcept>

// --- Определение f и df ---

double f(double x) {
    return x*x*x - 2.0*x - 5.0; // вариант 1
}

double df(double x) {
    return 3.0*x*x - 2.0;
}

// --- Метод половинного деления ---
Result bisection(double a, double b, double eps, int maxIter) {
    if (a >= b) throw std::invalid_argument("a must be < b");
    double fa = f(a);
    double fb = f(b);
    if (fa * fb > 0) throw std::invalid_argument("f(a) and f(b) must have opposite signs");

    Result res;
    res.iterations = 0;

    double left = a, right = b;
    for (int n = 0; n < maxIter; ++n) {
        double c = 0.5*(left + right);
        double fc = f(c);
        IterRecord rec;
        rec.iter = n;
        rec.x = c;
        rec.fx = fc;
        rec.delta = 0.5*(right - left); // полуинтервал
        res.history.push_back(rec);

        res.iterations = n+1;
        if (std::fabs(fc) < eps || (right - left)/2.0 < eps) {
            res.root = c;
            res.residual = std::fabs(fc);
            return res;
        }
        if (fa * fc < 0) {
            right = c; fb = fc;
        } else {
            left = c; fa = fc;
        }
    }
    double c = 0.5*(left + right);
    res.root = c;
    res.residual = std::fabs(f(c));
    return res;
}

// --- Метод простой итерации ---
Result simple_iteration(const std::function<double(double)>& phi, double x0, double eps, int maxIter) {
    Result res;
    double x = x0;
    res.iterations = 0;
    for (int n = 0; n < maxIter; ++n) {
        double xnext = phi(x);
        double fx = f(xnext);
        IterRecord rec;
        rec.iter = n;
        rec.x = xnext;
        rec.fx = fx;
        rec.delta = std::fabs(xnext - x);
        res.history.push_back(rec);

        res.iterations = n+1;
        if (rec.delta < eps || std::fabs(fx) < eps) {
            res.root = xnext;
            res.residual = std::fabs(fx);
            return res;
        }
        x = xnext;
    }
    res.root = x;
    res.residual = std::fabs(f(x));
    return res;
}

// --- Метод Ньютона ---
Result newton(double x0, double eps, int maxIter) {
    Result res;
    double x = x0;
    res.iterations = 0;
    for (int n = 0; n < maxIter; ++n) {
        double fx = f(x);
        double dfx = df(x);
        if (std::fabs(dfx) < 1e-14) {
            res.root = x;
            res.residual = std::fabs(fx);
            return res;
        }
        double xnext = x - fx/dfx;
        IterRecord rec;
        rec.iter = n;
        rec.x = xnext;
        rec.fx = f(xnext);
        rec.delta = std::fabs(xnext - x);
        res.history.push_back(rec);

        res.iterations = n+1;
        if (rec.delta < eps || std::fabs(rec.fx) < eps) {
            res.root = xnext;
            res.residual = std::fabs(rec.fx);
            return res;
        }
        x = xnext;
    }
    res.root = x;
    res.residual = std::fabs(f(x));
    return res;
}
