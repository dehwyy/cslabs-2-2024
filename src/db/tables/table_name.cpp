#include "table_name.h"
#include <stdexcept>

namespace table_name {
    std::string TableToString(Table table) {
        switch (table) {
            case Table::Planets:
                return PLANETS;
            case Table::Shops:
                return SHOPS;
            default:
                throw std::runtime_error("Unknown table!");
        }
    }

    Table TableFromString(std::string table_name) {
        if (table_name == PLANETS) {
            return Table::Planets;
        } else if (table_name == SHOPS) {
            return Table::Shops;
        }

        throw std::runtime_error("Unknown table");
    }
}  // namespace table_name
