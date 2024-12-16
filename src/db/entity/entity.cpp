#include "entity.h"
#include "../serde/serde.h"

namespace entity {
    bool operator==(const Entity& e1, const Entity& e2) {
        return e1.GetCompareValue() == e2.GetCompareValue();
    }

    bool operator<(const Entity& e1, const Entity& e2) {
        return e1.GetCompareValue() < e2.GetCompareValue();
    }

    int PlanetEntity::last_id = 0;

    PlanetEntity::PlanetEntity(int id, std::string name, int diameter, bool has_life, int satellites) {
        if (id <= 0) {
            id = ++this->last_id;
        } else {
            this->last_id = std::max(this->last_id, id);
        }

        std::cout << "New Planet entity with ID: " << id << std::endl;

        this->id = id;
        this->name = name;
        this->diameter = diameter;
        this->has_life = has_life;
        this->satellites = satellites;
    }

    PlanetEntity::~PlanetEntity() {
        std::cout << "Deleting Planet entity with ID: " << this->id << std::endl;
    }

    int PlanetEntity::GetId() {
        return this->id;
    }

    table_name::Table PlanetEntity::GetRelatedTable() {
        return table_name::Table::Planets;
    }

    std::vector<std::string> PlanetEntity::Serialize() {
        std::vector<std::string> out;

        out.emplace_back("id");
        out.push_back(std::to_string(id));
        out.emplace_back("name");
        out.push_back(name);
        out.emplace_back("diameter");
        out.push_back(std::to_string(diameter));
        out.emplace_back("has_life");
        out.emplace_back(has_life ? "1" : "0");
        out.emplace_back("satellites");
        out.push_back(std::to_string(satellites));

        return out;
    }

    int PlanetEntity::GetCompareValue() const {
        return this->diameter;
    }

    std::istream& operator>>(std::istream& s, PlanetEntity*& pl) {
        std::string line = "";
        while (!s.eof()) {
            std::getline(s, line);
            auto entity = serde::Deserializer::FromString(line);
            if (!entity) {
                entity.release();
                pl = nullptr;
                break;
            }

            auto casted_entity = dynamic_cast<entity::PlanetEntity*>(entity.release());
            if (!casted_entity) {
                delete casted_entity;
                pl = nullptr;
                break;
            }

            pl->id = casted_entity->id;
            pl->name = casted_entity->name;
            pl->diameter = casted_entity->diameter;
            pl->has_life = casted_entity->has_life;
            pl->satellites = casted_entity->satellites;

            break;
        }

        return s;
    }

    std::ostream& operator<<(std::ostream& s, PlanetEntity* pl) {
        if (!pl) {
            return s;
        }

        auto args = pl->Serialize();
        for (size_t i = 0; i < args.size(); i += 2) {
            std::cout << args.at(i) << ": " << args.at(i + 1);
            if (i < args.size() - 2) {
                std::cout << ", ";
            }
        }

        return s;
    }

    int ShopEntity::last_id = 0;

    ShopEntity::ShopEntity(int id,
                           std::string name,
                           std::string address,
                           std::string owner,
                           int employees,
                           int revenue_per_month) {
        if (id <= 0) {
            id = ++this->last_id;
        } else {
            this->last_id = std::max(this->last_id, id);
        }

        std::cout << "New Shop entity with ID: " << id << std::endl;

        this->id = id;
        this->name = name;
        this->address = address;
        this->owner = owner;
        this->employees = employees;
        this->revenue_per_month = revenue_per_month;
    }

    ShopEntity::~ShopEntity() {
        std::cout << "Deleting Shop entity with ID: " << this->id << std::endl;
    }

    int ShopEntity::GetId() {
        return this->id;
    }

    table_name::Table ShopEntity::GetRelatedTable() {
        return table_name::Table::Shops;
    }

    std::vector<std::string> ShopEntity::Serialize() {
        std::vector<std::string> out;

        out.emplace_back("id");
        out.push_back(std::to_string(id));
        out.emplace_back("name");
        out.push_back(name);
        out.emplace_back("address");
        out.push_back(address);
        out.emplace_back("owner");
        out.push_back(owner);
        out.emplace_back("employees");
        out.push_back(std::to_string(employees));
        out.emplace_back("revenue_per_month");
        out.push_back(std::to_string(revenue_per_month));

        return out;
    }

    int ShopEntity::GetCompareValue() const {
        return this->revenue_per_month;
    }

}  // namespace entity
