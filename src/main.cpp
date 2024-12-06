#include <iostream>
#include "mymath/mymath.h"
#include "printer/printer.h"

int main() {
    printer::Print("Факторил числа 5: ");
    std::cout << math::factorial(5) << std::endl;

    printer::PrintLn("Вывод с переновом строки!");
    printer::Print("Вывод без переноса строки: - ");
    printer::PrintLn("Выполнено!");

    return 0;
}
