#include "app.hpp"
#include <iostream>
#include "../collections/vector.hpp"
#include "../state/state.hpp"

namespace {
    int BUFSIZE = 128;
}

namespace app {
    void RunDemo() {
        vector::Vec<state::State*> states = {};
        states.push_back(
            new state::Republic((char*)"Россия", 144820423, 17125191, (char*)"Владимир Путин", 4));

        states.push_back(new state::Monarchy((char*)"Казахстан",
                                             19398000,
                                             2724900,
                                             (char*)"Нурсултан Назарбаев",
                                             (char*)"Казахстанская монархия"));

        states.push_back(new state::Kingdom(
            (char*)"Турция", 87473805, 780580, (char*)"Эрдоган", (char*)"Королевство", (char*)"Ислам"));

        states.push_back(
            new state::Republic((char*)"Индия", 1450935791, 3287263, (char*)"Драупади Мурму", 4));

        states.print();
        std::cout << std::endl;

        std::cout << "remove(2):" << std::endl;
        states.remove(2);

        states.print();

        std::cout << "clear():" << std::endl;
        states.clear();

        std::cout << std::endl;
    }

    void RunInteractive() {
        std::cout << "Интерактивный режим:" << std::endl;
        vector::Vec<state::State*> states = {};
        while (true) {
            std::cout << "1 - добавить государство" << std::endl;
            std::cout << "2 - удалить государство" << std::endl;
            std::cout << "3 - вывести список" << std::endl;
            std::cout << "4 - выход" << std::endl;
            std::cout << "Ваш выбор: ";

            int choice = 0;
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    int type = 0;

                    while (type < 1 || type > 3) {
                        std::cout << "Введите тип государства: " << std::endl;
                        std::cout << "1 - Республика" << std::endl;
                        std::cout << "2 - Монархия" << std::endl;
                        std::cout << "3 - Королевство" << std::endl;

                        std::cin >> type;

                        if (type < 1 || type > 3) {
                            std::cout << "Некорректный ввод" << std::endl;
                        }
                    }

                    std::cout << "Введите название государства: ";
                    char* name = new char[BUFSIZE];
                    std::cin >> name;
                    std::cout << "Введите численность население: ";
                    int population = 0;
                    std::cin >> population;
                    std::cout << "Введите площадь: ";
                    double area = 0;
                    std::cin >> area;

                    switch (type) {
                        case 1: {
                            std::cout << "Введите президента: ";
                            char* president = new char[BUFSIZE];
                            std::cin >> president;
                            states.push_back(new state::Republic(name, population, area, president, 4));

                            delete[] president;
                            break;
                        }
                        case 2: {
                            std::cout << "Введите президента: ";
                            char* monarch = new char[BUFSIZE];
                            std::cin >> monarch;
                            states.push_back(new state::Monarchy(
                                name, population, area, monarch, (char*)"Казахстанская монархия"));

                            delete[] monarch;
                            break;
                        }
                        case 3: {
                            std::cout << "Введите президента: ";
                            char* monarch = new char[BUFSIZE];
                            std::cin >> monarch;
                            std::cout << "Введите тип королевства: ";
                            char* monarchyType = new char[BUFSIZE];
                            std::cin >> monarchyType;
                            states.push_back(new state::Kingdom(
                                name, population, area, monarch, (char*)"Королевство", monarchyType));

                            delete[] monarch;
                            delete[] monarchyType;
                            break;
                        }
                    }

                    break;
                }
                case 2: {
                    std::cout << "Введите индекс государства: ";
                    int index = 0;
                    std::cin >> index;
                    if (index < 0 || index >= states.size()) {
                        std::cout << "Некорректный ввод" << std::endl;
                    } else {
                        states.remove(index);
                    }

                    break;
                }
                case 3:
                    if (states.size() == 0) {
                        std::cout << "Список пуст" << std::endl;
                    } else {
                        states.print();
                    }
                    break;
                case 4:
                    return;
                default:
                    std::cout << "Некорректный ввод" << std::endl;
            }
        }
    }
}  // namespace app
