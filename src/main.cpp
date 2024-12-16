#include <fstream>
#include <iostream>
#include <memory>
#include "db/db.h"
#include "db/tables/tables.h"

int main() {
    auto db = new db::Database("db.db");

    db->PrintAll();
    int id = db->InsertOne(std::make_unique<entity::PlanetEntity>(-1, "Psyh", 333, false, 12));

    db->PrintAll();

    db->DeleteOne(table_name::Table::Planets, 1);
    db->DeleteOne(table_name::Table::Planets, id);
    db->PrintAll();
    // db->SortTables();
    // db->PrintAll();

    db->SyncWithFile();

    // std::fstream f;
    // db->GetRawReader(f, table_name::Table::Planets);

    // auto planet = new entity::PlanetEntity();
    // while (planet) {
    //     f >> planet;
    //     if (planet) {
    //         std::cout << planet << std::endl;
    //     }
    // }

    return 0;
}
