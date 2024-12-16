#pragma once
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include "serde/serde.h"
#include "tables/tables.h"

namespace db {

    class Database {
        private:
            std::string filepath = "";
            std::unordered_map<table_name::Table, tables::DbTable*> tables = {};

            void AddToTable(std::unique_ptr<entity::Entity>);

        public:
            Database(std::string filepath);
            ~Database() = default;

            void SyncWithFile();
            void SortTables();
            int InsertOne(std::unique_ptr<entity::Entity>);
            void DeleteOne(table_name::Table table, int id);
            void PrintTable(table_name::Table);
            void PrintAll();
            void GetRawReader(std::fstream& reader, table_name::Table table_name);
    };
}  // namespace db
