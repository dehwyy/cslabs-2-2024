#include <fstream>
#include <iostream>
#include <memory>
#include "db/db.h"
#include "db/tables/tables.h"
#include "interaction/interaction.h"

void Run();
void RunRawReader();

int main() {
    Run();
    // RunRawReader();
    return 0;
}

void Run() {
    auto db = new db::Database("db.db");

    while (true) {
        table_name::Table table;
        auto interactionType = interaction::ReadEntityInteractionType();
        switch (interactionType) {
            case interaction::EntityType::Planet:
                table = table_name::Table::Planets;
                break;
            case interaction::EntityType::Shop:
                table = table_name::Table::Shops;
                break;
            default:
                exit(1);
        }

        bool isExit = false;
        while (!isExit) {
            switch (interaction::ReadDatabaseInteractionType()) {
                case interaction::DatabaseInteractionType::Insert:
                    std::cout << "Добавление сущности:" << std::endl;
                    switch (interactionType) {
                        case interaction::EntityType::Planet:
                            db->InsertOne(interaction::ReadPlanetEntity());
                            break;
                        case interaction::EntityType::Shop:
                            db->InsertOne(interaction::ReadShopEntity());
                            break;
                        default:
                            std::cout << "Некорректный тип сущности!" << std::endl;
                            exit(1);
                    }

                    break;
                case interaction::DatabaseInteractionType::Delete:
                    std::cout << "Удаление сущности:" << std::endl;
                    db->DeleteOne(table, interaction::ReadEntityId());
                    break;
                case interaction::DatabaseInteractionType::Sort:
                    db->SortTables();
                    std::cout << "Таблицы отсортированы" << std::endl;
                    break;
                case interaction::DatabaseInteractionType::SyncWithFile:
                    db->SyncWithFile();
                    std::cout << "Синхронизация с файлом" << std::endl;
                    break;
                case interaction::DatabaseInteractionType::Print:
                    db->PrintTable(table);
                    break;
                case interaction::DatabaseInteractionType::Stop:
                    std::cout << "Завершение программы" << std::endl;
                    exit(0);
                case interaction::DatabaseInteractionType::SwitchTable:
                    std::cout << "Смена таблицы" << std::endl;
                    isExit = true;
                    break;
            }
        }
    }
}

void RunRawReader() {
    auto db = new db::Database("db.db");

    std::fstream f;
    db->GetRawReader(f, table_name::Table::Planets);

    auto planet = new entity::PlanetEntity();
    while (planet) {
        f >> planet;
        if (planet) {
            std::cout << planet << std::endl;
        }
    }
}
