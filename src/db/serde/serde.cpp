#include "serde.h"
#include <iostream>
#include "../tables/table_name.h"

namespace serde {
    const char TABLE_NAME_DELIM = '#';
    const char FIELD_DELIM = ';';
    const char KEY_VALUE_DELIM = '=';
    const char SPACE = ' ';

    std::unique_ptr<entity::Entity> Deserializer::FromString(std::string s) {
        size_t pos = s.find(TABLE_NAME_DELIM);

        if (pos == std::string::npos) {
            return nullptr;
        }

        auto table = table_name::TableFromString(s.substr(0, pos));

        auto tokens = std::vector<std::string>();
        std::string token = "";

        while ((pos = s.find(FIELD_DELIM)) != std::string::npos) {
            token = s.substr(0, pos);
            token = token.substr(token.find(KEY_VALUE_DELIM) + 1);

            tokens.push_back(token);
            s.erase(0, pos + 1);
        }

        if (table == table_name::Table::Planets) {
            return std::make_unique<entity::PlanetEntity>(
                std::stoi(tokens.at(0)), tokens.at(1), std::stoi(tokens.at(2)), std::stoi(tokens.at(3)),
                std::stoi(tokens.at(4)));
        }

        if (table == table_name::Table::Shops) {
            return std::make_unique<entity::ShopEntity>(
                std::stoi(tokens.at(0)), tokens.at(1), tokens.at(2), tokens.at(3),
                std::stoi(tokens.at(4)), std::stoi(tokens.at(5)));
        }

        return nullptr;
    }

    std::string Serializer::Serialize(entity::Entity& entity) {
        auto args = entity.Serialize();

        std::string out = table_name::TableToString(entity.GetRelatedTable());
        out += TABLE_NAME_DELIM;

        for (size_t i = 0; i < args.size(); i++) {
            out += args.at(i);
            out += i % 2 == 0 ? KEY_VALUE_DELIM : FIELD_DELIM;
        }

        return out;
    }

    std::string Serializer::Pretty(entity::Entity& entity) {
        auto args = entity.Serialize();

        std::string out = table_name::TableToString(entity.GetRelatedTable()) + " ";
        for (size_t i = 0; i < args.size(); i++) {
            out += args.at(i);
            out += i % 2 == 0 ? KEY_VALUE_DELIM : SPACE;
        }

        return out;
    }
}  // namespace serde
