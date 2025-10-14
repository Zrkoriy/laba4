#pragma once
#include <functional>
#include <vector>

struct IterRecord {
    int iter;
    double x;       // приближение
    double fx;      // f(x)
    double delta;   // |x - prev_x| (для методов итерации/Ньютона), или половина интервала для бисекции
};

struct Result {
    double root;
    int iterations;
    double residual; // |f(root)|
    std::vector<IterRecord> history;
};

// Основная целевая функция (вариант 1): f(x) = x^3 - 2x - 5
double f(double x);
// Производная f'(x) = 3x^2 - 2
double df(double x);

// Метод половинного деления. a,b - начальный интервал (требуется f(a)*f(b) < 0).
// eps - требуемая абсолютная точность по корню (стоп-критерий: (b-a)/2 < eps OR |f(c)| < eps).
// maxIter - максимальное число итераций.
Result bisection(double a, double b, double eps, int maxIter = 1000);

// Метод простой итерации (фиксированная итерация через phi):
// phi - функция итерации (x_{n+1} = phi(x_n)).
// x0 - начальное приближение.
// eps - требуемая точность по шагу и/или по невязке.
// maxIter - максимальное число итераций.
Result simple_iteration(const std::function<double(double)>& phi, double x0, double eps, int maxIter = 10000);

// Метод Ньтона. x0 - начальное приближение.
Result newton(double x0, double eps, int maxIter = 1000);
