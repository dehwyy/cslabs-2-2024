#include "app.hpp"
#include <iostream>

namespace {
    template <typename T>
    void PrintSetOperations(set::Set<T> s1, set::Set<T> s2) {
        std::cout << "Введеное множество: " << s2 << std::endl;
        std::cout << "Пересечение множеств: " << s1 * s2 << std::endl;
        std::cout << "Объединение множеств: " << s1 + s2 << std::endl;
        std::cout << "Разность множеств: " << s1 - s2 << std::endl << std::endl;

        std::cout << "Множества после операций: " << std::endl;
        std::cout << "Исходное множество: " << s1 << std::endl;
        std::cout << "Множество, введеное с клавиатуры: " << s2 << std::endl;
    }
}  // namespace

namespace app {
    void RunIntTask() {
        set::Set<int> set;
        for (int i = 20; i > 2; i -= 2) {
            set.add(i);
        }

        std::cout << "Множество: " << set << std::endl;

        set.remove(6);
        std::cout << "Множество после удаления `6`: " << set << std::endl;

        set.add(13);
        std::cout << "Множество после добавления `13`: " << set << std::endl;

        set.add(20);
        std::cout << "Множество после добавления `20`: " << set << std::endl;

        std::cout << "Есть ли в множестве `13`?: " << (set.has(13) ? "Да" : "Нет") << std::endl;
        std::cout << "Есть ли в множестве `6`?: " << (set.has(6) ? "Да" : "Нет") << std::endl
                  << std::endl;

        std::cout << "Введите целые числа через пробел: ";
        set::Set<int> newSet;
        std::cin >> newSet;

        PrintSetOperations(set, newSet);
    }

    void RunCStringTask() {
        set::Set<char*> set;

        set.add((char*)"Hello");
        set.add((char*)"World");
        set.add((char*)"!");

        std::cout << "Множество: " << set << std::endl;

        set.remove((char*)"!");
        std::cout << "Множество после удаления `!`: " << set << std::endl;

        set.add((char*)"?");
        std::cout << "Множество после добавления `?`: " << set << std::endl;

        std::cout << "Есть ли в множестве `?`?: " << (set.has((char*)"?") ? "Да" : "Нет") << std::endl;
        std::cout << "Есть ли в множестве `!`?: " << (set.has((char*)"!") ? "Да" : "Нет") << std::endl
                  << std::endl;

        std::cout << "Введите слова через пробел: ";
        set::Set<char*> newSet;
        std::cin >> newSet;

        PrintSetOperations(set, newSet);
    }

}  // namespace app
