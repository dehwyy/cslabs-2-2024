#pragma once

#include <string>

namespace tables {
    const char FIELD_DELIM = ';';
    const char KEY_VALUE_DELIM = '=';

    class DbTable {
        public:
            virtual std::string GetName() = 0;
            // virtual std::string Serialize();
            virtual void Parse(std::string line) = 0;

            DbTable() = default;
            virtual ~DbTable() = default;
    };

    const std::string DbTablePlanetsName = "PLANETS";
    class DbTablePlanets : public DbTable {
        private:
            std::string name = "";
            int diameter = 0;
            bool has_life = false;
            int satellites = 0;

        public:
            DbTablePlanets() = default;
            std::string GetName() override;
            std::string Serialize();
            void Parse(std::string line) override;

            std::string GetPlanetName() { return this->name; }
            int GetDiameter() { return this->diameter; }
            bool HasLife() { return this->has_life; }
            int GetSatellites() { return this->satellites; }
    };

    const std::string DbTableShopName = "SHOP";
    class DbTableShop : public DbTable {
        private:
            std::string name = "";
            std::string address = "";
            std::string owner = "";
            int employees = 0;
            int revenue_per_month = 0;
            int sell_price = 0;

        public:
            DbTableShop() = default;
            std::string GetName() override;
            std::string Serialize();
            void Parse(std::string line) override;
    };
}  // namespace tables
