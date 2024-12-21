#pragma once
#include "../collections/stack/stack.hpp"

namespace app {
    void FactorizeNumber(int number, stack::Stack<int>& stack);

    void PrintIntStack(stack::Stack<int> stack);
}  // namespace app
