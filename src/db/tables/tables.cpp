#include "tables.h"
#include <iostream>
#include "../../collections/vec.h"

namespace tables {
    std::string DbTablePlanets::GetName() {
        return DbTablePlanetsName;
    }
    void DbTablePlanets::Parse(std::string line) {
        auto tokens = vec::Vector<std::string>();
        size_t pos = 0;
        std::string token = "";

        while ((pos = line.find(FIELD_DELIM)) != std::string::npos) {
            token = line.substr(0, pos);
            token = token.substr(token.find(KEY_VALUE_DELIM) + 1);

            tokens.PushBack(token);
            line.erase(0, pos + 1);
        }
        if (line.length() > 0) {
            tokens.PushBack(line);
        }

        this->name = tokens.Get(1);
        this->diameter = std::stoi(tokens.Get(2));
        this->has_life = std::stoi(tokens.Get(3));
        this->satellites = std::stoi(tokens.Get(4));
    }

    std::string DbTablePlanets::Serialize() {
        return "";
    }

    void DbTableShop::Parse(std::string line) {
        this->address = line;
    }

    std::string DbTableShop::GetName() {
        return DbTableShopName;
    }

    std::string DbTableShop::Serialize() {
        return "";
    }
}  // namespace tables
