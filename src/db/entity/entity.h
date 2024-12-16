#pragma once

#include <iostream>
#include <string>
#include "../tables/table_name.h"
#include "vector"

namespace entity {
    class Entity {
        public:
            virtual ~Entity() = default;
            virtual int GetId() = 0;
            virtual table_name::Table GetRelatedTable() = 0;
            virtual std::vector<std::string> Serialize() = 0;

            virtual int GetCompareValue() const = 0;
            friend bool operator<(const Entity& e1, const Entity& e2);
            friend bool operator==(const Entity& e1, const Entity& e2);
    };

    class PlanetEntity : public Entity {
        public:
            static int last_id;
            int id = 0;
            std::string name = "";
            int diameter = 0;
            bool has_life = false;
            int satellites = 0;

            int GetId() override;
            table_name::Table GetRelatedTable() override;
            std::vector<std::string> Serialize() override;
            int GetCompareValue() const override;

            PlanetEntity() = default;
            PlanetEntity(int id, std::string name, int diameter, bool has_life, int satellites);
            ~PlanetEntity();

            friend std::istream& operator>>(std::istream& s, PlanetEntity*& p);
            friend std::ostream& operator<<(std::ostream& s, PlanetEntity* p);
    };

    class ShopEntity : public Entity {
        public:
            static int last_id;
            int id = 0;
            std::string name = "";
            std::string address = "";
            std::string owner = "";
            int employees = 0;
            int revenue_per_month = 0;

            int GetId() override;
            table_name::Table GetRelatedTable() override;
            std::vector<std::string> Serialize() override;
            int GetCompareValue() const override;

            ShopEntity() = default;
            ShopEntity(int id,
                       std::string name,
                       std::string address,
                       std::string owner,
                       int employees,
                       int revenue_per_month);
            ~ShopEntity();
    };
}  // namespace entity
