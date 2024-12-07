#pragma once
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include "../collections/key_value.h"
#include "../collections/vec.h"
#include "tables/tables.h"

namespace db {

    const std::string T_PLANETS = "Planets";
    const std::string DELIM = ";";

    struct SchemaPlanet {
            std::string name = "";
            int diameter = 0;
            bool has_life = false;
            int satellites = 0;
    };

    class Db {
        private:
            static std::string ReadOnce(std::istream& s);
            static SchemaPlanet* ParsePlanet(std::string line);

        public:
            static std::ifstream Open(std::string filepath);
            static SchemaPlanet* GetPlanetOnce(std::istream& s);
    };

    class Db2 {
        private:
            const char* const INDEX_FILEPATH = "index.db";
            const char KEY_VALUE_DELIM = '=';
            const char PREFIX_DELIM = '#';

            std::string filepath = "";
            std::fstream file_handle = {};
            std::fstream index_file_handle = {};
            std::unordered_map<std::string, unsigned> tables = {};

            void RemovePrefix(std::string& line);
            void InitDbIndexes();

        public:
            Db2(std::string filepath);
            ~Db2();

            void GetOne(tables::DbTable& table);
    };
}  // namespace db
