#include "app.hpp"
#include <iostream>

namespace app {
    void RunExample() {
        polynomial::Polynomial p = {};
        std::cout << "Введите полином: ";
        std::cin >> p;
        std::cout << "Введенный полином: " << p << std::endl;

        polynomial::Polynomial p2 = {};
        std::cout << "Введите второй полином: ";
        std::cin >> p2;
        std::cout << "Введенный второй полином: " << p2 << std::endl;

        std::cout << "Сумма полиномов: " << p + p2 << std::endl;

        std::cout << "Произведение полиномов: " << p * p2 << std::endl;
    }

    void RunTermExample() {
        using namespace polynomial;

        term::Term t = {};
        std::cout << "Введите терм: ";
        std::cin >> t;
        std::cout << "Введенный терм: " << t << std::endl;

        term::Term t2 = {};
        std::cout << "Введите второй терм той же степени: ";
        std::cin >> t2;
        std::cout << "Введенный второй терм: " << t2 << std::endl;

        std::cout << "Сумма термов: " << t + t2 << std::endl;

        std::cout << "Произведение термов: " << t * t2 << std::endl;
    }
}  // namespace app
