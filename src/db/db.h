#pragma once
#include <iostream>
#include <string>
#include "../collections/vec.h"

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
}  // namespace db
