#include "state.hpp"
#include <cstring>
#include <iostream>

namespace state {
    State::State(char* name, int population, double area, char* governmentType) {
        this->name = new char[strlen(name) + 1];
        this->governmentType = new char[strlen(governmentType) + 1];

        strncpy(this->name, name, strlen(name) + 1);
        strncpy(this->governmentType, governmentType, strlen(governmentType) + 1);

        this->population = population;
        this->area = area;
    }

    State::~State() {
        delete[] this->name;
        delete[] this->governmentType;
    }

    double State::calculateDensity() const {
        return static_cast<double>(this->population) / this->area;
    }

    void State::show() const {
        std::cout << "Название государства: " << this->name << std::endl;
        std::cout << "Население: " << this->population << std::endl;
        std::cout << "Площадь: " << this->area << std::endl;
        std::cout << "Тип правления: " << this->governmentType << std::endl;
        std::cout << "Плотность: " << this->calculateDensity() << std::endl;
    }

    Republic::Republic(char* name, int population, double area, char* president, int presidentTermLength)
        : State(name, population, area, (char*)"Республика") {
        this->president = new char[strlen(president) + 1];
        this->presidentTermLength = presidentTermLength;

        strncpy(this->president, president, strlen(president) + 1);
    }

    Republic::~Republic() {
        delete[] this->president;
    }

    void Republic::show() const {
        this->State::show();
        std::cout << "Президент: " << this->president << std::endl;
        std::cout << "Срок срока: " << this->presidentTermLength << std::endl;
    }

    Monarchy::Monarchy(char* name, int population, double area, char* monarch, char* monarchyType)
        : State(name, population, area, monarchyType) {
        this->monarch = new char[strlen(monarch) + 1];
        strncpy(this->monarch, monarch, strlen(monarch) + 1);
    }

    Monarchy::~Monarchy() {
        delete[] this->monarch;
    }

    void Monarchy::show() const {
        this->State::show();
        std::cout << "Монарх: " << this->monarch << std::endl;
    }

    Kingdom::Kingdom(char* name,
                     int population,
                     double area,
                     char* monarch,
                     char* monarchyType,
                     char* mainReligion)
        : Monarchy(name, population, area, monarch, monarchyType) {
        this->mainReligion = new char[strlen(mainReligion) + 1];
        strncpy(this->mainReligion, mainReligion, strlen(mainReligion) + 1);
    }

    Kingdom::~Kingdom() {
        delete[] this->mainReligion;
    }

    void Kingdom::show() const {
        this->State::show();
        std::cout << "Религия: " << this->mainReligion << std::endl;
    }
}  // namespace state
