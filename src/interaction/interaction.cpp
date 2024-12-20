#include "interaction.h"
#include <iostream>

namespace {
    bool isValidEntityType(int v) {
        return v > 0 && v < 3;
    }

    bool isValidDatabaseInteractionType(int v) {
        return v > 0 && v < 8;
    }
}  // namespace

namespace interaction {
    EntityType ReadEntityInteractionType() {
        int type = 0;
        while (!isValidEntityType(type)) {
            std::cout << "Введите тип сущности (1 - планета, 2 - магазин): ";
            std::cin >> type;

            if (!isValidEntityType(type)) {
                std::cout << "Некорректный тип сущности!" << std::endl;
            }
        }

        return static_cast<EntityType>(type);
    }

    std::unique_ptr<entity::PlanetEntity> ReadPlanetEntity() {
        int id = -1;

        std::string name = "";
        int diameter = 0;
        bool has_life = false;
        int satellites = 0;

        std::cout << "Название планеты: ";
        std::cin >> name;
        std::cout << "Диаметр: ";
        std::cin >> diameter;
        std::cout << "Есть жизнь? (1 - да, 0 - нет): ";
        std::cin >> has_life;
        std::cout << "Кол-во спутников: ";
        std::cin >> satellites;

        return std::make_unique<entity::PlanetEntity>(id, name, diameter, has_life, satellites);
    }

    std::unique_ptr<entity::ShopEntity> ReadShopEntity() {
        int id = -1;

        std::string name = "";
        std::string address = "";
        std::string owner = "";
        int employees = 0;
        int revenue_per_month = 0;

        std::cout << "Название магазина: ";
        std::cin >> name;
        std::cout << "Адрес магазина: ";
        std::cin >> address;
        std::cout << "Имя владельца: ";
        std::cin >> owner;
        std::cout << "Кол-во сотрудников: ";
        std::cin >> employees;
        std::cout << "Выручка в месяц: ";
        std::cin >> revenue_per_month;

        return std::make_unique<entity::ShopEntity>(
            id, name, address, owner, employees, revenue_per_month);
    }

    DatabaseInteractionType ReadDatabaseInteractionType() {
        int type = 0;
        while (!isValidDatabaseInteractionType(type)) {
            std::cout << "Введите тип деЙствия (1 - вставка, 2 - удаление, 3 - сортировка, 4 - "
                         "синхронизация, 5 - печать, 6 - выход, 7 - смена таблицы): ";
            std::cin >> type;

            if (!isValidDatabaseInteractionType(type)) {
                std::cout << "Некорректный тип действия!" << std::endl;
            }
        }

        return static_cast<DatabaseInteractionType>(type);
    }

    int ReadEntityId() {
        int id = 0;
        std::cout << "Введите ID сущности: ";
        std::cin >> id;
        return id;
    }
}  // namespace interaction
