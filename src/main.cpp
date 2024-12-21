#include <iostream>
#include "app/app.hpp"

int main() {
    std::cout << "Множество из целых чисел: " << std::endl;
    app::RunIntTask();

    std::cout << "Множество из строк: " << std::endl;
    app::RunCStringTask();
    return 0;
}
