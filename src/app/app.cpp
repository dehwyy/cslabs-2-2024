#include "app.hpp"
#include <iostream>

namespace app {
    void FactorizeNumber(int number, stack::Stack<int>& stack) {
        for (int i = 2; i <= number; i++) {
            while (number % i == 0) {
                stack.push(i);
                number /= i;
            }
        }
    }

    void PrintIntStack(stack::Stack<int> stack) {
        int size = stack.get_size();
        for (int i = 0; i < size; ++i) {
            std::cout << stack.pop();
            if (i != size - 1) {
                std::cout << " * ";
            }
        }
        std::cout << std::endl;
    }
}  // namespace app
