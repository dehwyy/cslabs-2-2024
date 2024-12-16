#pragma once
#include <string>

namespace table_name {
    const std::string PLANETS = "PLANETS";
    const std::string SHOPS = "SHOPS";

    enum class Table { Planets, Shops };

    std::string TableToString(Table);
    Table TableFromString(std::string);
}  // namespace table_name
