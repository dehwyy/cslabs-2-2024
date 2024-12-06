#include <iostream>

namespace printer {
    void Print(const char* message) {
        std::cout << message;
    }

    void PrintLn(const char* message) {
        std::cout << message << std::endl;
    }
}  // namespace printer
