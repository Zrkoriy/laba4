#include "../include/methods.hpp"
#include "../include/utils.hpp"
#include <iostream>
#include <cmath>

int main() {
    print_header();

    double a = 1.0; // f(1) = -6 < 0
    double b = 3.0; // f(3) = 13 > 0  -> корень между 1 и 3
    double x0_newton = 2.0;
    double x0_simple = 2.0;

    double eps1 = 1e-6;
    double eps2 = 1e-11;

    print_table_header("Метод бисекции", eps1);
    try {
        Result rb1 = bisection(a, b, eps1);
        for (const auto &r : rb1.history) print_record(r);
        std::cout << "результат: корень=" << rb1.root << ", итерации=" << rb1.iterations << ", |f|=" << rb1.residual << "\n";
    } catch (const std::exception &ex) {
        std::cerr << "Ошибка бисекции: " << ex.what() << "\n";
    }

    print_table_header("Метод бисекции", eps2);
    try {
        Result rb2 = bisection(a, b, eps2, 2000);
        for (const auto &r : rb2.history) print_record(r);
        std::cout << "результат: корень=" << rb2.root << ", итерации=" << rb2.iterations << ", |f|=" << rb2.residual << "\n";
    } catch (const std::exception &ex) {
        std::cerr << "Ошибка бисекции: " << ex.what() << "\n";
    }

    double lambda = 0.1;
    auto phi_relax = [lambda](double x) { return x - lambda * (x*x*x - 2.0*x - 5.0); };

    print_table_header("Метод простой итерации (релаксация)", eps1);
    Result rs1 = simple_iteration(phi_relax, x0_simple, eps1, 10000);
    for (const auto &r : rs1.history) print_record(r);
    std::cout << "результат: корень=" << rs1.root << ", итерации=" << rs1.iterations << ", |f|=" << rs1.residual << "\n";

    print_table_header("Метод простой итерации (релаксация)", eps2);
    Result rs2 = simple_iteration(phi_relax, x0_simple, eps2, 200000);
    for (const auto &r : rs2.history) print_record(r);
    std::cout << "результат: корень=" << rs2.root << ", итерации=" << rs2.iterations << ", |f|=" << rs2.residual << "\n";

    print_table_header("Метод Ньютона", eps1);
    Result rn1 = newton(x0_newton, eps1);
    for (const auto &r : rn1.history) print_record(r);
    std::cout << "результат: корень=" << rn1.root << ", итерации=" << rn1.iterations << ", |f|=" << rn1.residual << "\n";

    print_table_header("Метод Ньютона", eps2);
    Result rn2 = newton(x0_newton, eps2, 1000);
    for (const auto &r : rn2.history) print_record(r);
    std::cout << "результат: корень=" << rn2.root << ", итерации=" << rn2.iterations << ", |f|=" << rn2.residual << "\n";

    return 0;
}
