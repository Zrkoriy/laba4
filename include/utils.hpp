#pragma once
#include <iostream>
#include <iomanip>
#include "methods.hpp"

inline void print_header() {
    std::cout << std::fixed << std::setprecision(10);
}

inline void print_table_header(const std::string &method_name, double eps) {
    std::cout << "\n=== " << method_name << " (eps=" << eps << ") ===\n";
    std::cout << std::setw(6) << "iter"
              << std::setw(18) << "x"
              << std::setw(18) << "f(x)"
              << std::setw(14) << "delta"
              << "\n";
    std::cout << std::string(60, '-') << "\n";
}

inline void print_record(const IterRecord &r) {
    std::cout << std::setw(6) << r.iter
              << std::setw(18) << r.x
              << std::setw(18) << r.fx
              << std::setw(14) << r.delta << "\n";
}
