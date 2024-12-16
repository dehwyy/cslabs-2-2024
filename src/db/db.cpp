#include "db.h"
#include <iomanip>

namespace {
    void Printline(char c, int w) {
        std::cout << std::setfill(c) << std::setw(w) << " " << std::setfill(' ') << std::endl;
    }
}  // namespace

namespace db {
    void Database::AddToTable(std::unique_ptr<entity::Entity> entity) {
        auto table_name = entity.get()->GetRelatedTable();

        if (this->tables.find(table_name) == this->tables.end()) {
            this->tables[table_name] = new tables::DbTable();
        }

        this->tables[table_name]->AddEntity(std::move(entity));
    }

    Database::Database(std::string filepath) {
        this->filepath = filepath;

        this->SyncWithFile();
    }

    void Database::SyncWithFile() {
        // Empty -> read from file and store to structure
        if (tables.empty()) {
            std::fstream f(this->filepath.c_str(), std::ios::binary | std::ios::in | std::ios::out);

            std::string line = "";
            while (!f.eof()) {
                std::getline(f, line);
                std::unique_ptr<entity::Entity> entity = serde::Deserializer::FromString(line);

                if (!entity) {
                    entity.release();
                    continue;
                }

                this->AddToTable(std::move(entity));
            }

            f.close();
            return;
        }

        // Otherwise -> write to file
        std::ofstream f(this->filepath.c_str(), std::ios::binary | std::ios::out | std::ios::trunc);
        for (auto kv : this->tables) {
            auto table = kv.second;

            f << table_name::TableToString(kv.first) << std::endl;
            for (auto& entity : table->GetEntities()) {
                f << serde::Serializer::Serialize(*entity) << std::endl;
            }
        }

        f.close();
    }

    void Database::SortTables() {
        for (auto kv : this->tables) {
            kv.second->Sort();
        }
    }

    int Database::InsertOne(std::unique_ptr<entity::Entity> entity) {
        int id = entity->GetId();
        this->AddToTable(std::move(entity));

        return id;
    }

    void Database::DeleteOne(table_name::Table table, int id) {
        this->tables[table]->RemoveEntity(id);
    }

    void Database::PrintTable(table_name::Table table_name) {
        auto table = this->tables[table_name];

        std::cout << "Table: " << table_name::TableToString(table_name) << std::endl;

        for (auto& entity : table->GetEntities()) {
            std::cout << serde::Serializer::Pretty(*entity) << std::endl;
        }
    }

    void Database::PrintAll() {
        Printline('-', 100);
        for (auto kv : this->tables) {
            std::cout << std::endl;
            this->PrintTable(kv.first);
        }
        std::cout << std::endl;
        Printline('-', 100);
    }

    void Database::GetRawReader(std::fstream& f, table_name::Table table_name) {
        f.open(this->filepath.c_str(), std::ios::binary | std::ios::in | std::ios::out);

        f.seekg(0, std::ios::beg);

        std::string line = "";
        while (!f.eof()) {
            std::getline(f, line);
            if (line == table_name::TableToString(table_name)) {
                break;
            }
        }
    }
}  // namespace db
