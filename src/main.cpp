#include <iostream>
#include "app/app.hpp"
#include "collections/stack/stack.hpp"

int main() {
    int number = 0;
    std::cout << "Введите число(int): ";
    std::cin >> number;

    stack::Stack<int> stack;
    app::FactorizeNumber(number, stack);

    std::cout << number << "=";
    app::PrintIntStack(stack);
    stack.reverse();

    std::cout << number << "=";
    app::PrintIntStack(stack);
    return 0;
}
