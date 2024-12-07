#include "planets.h"
#include "cstring"

namespace planets {
    Planet::Planet() = default;
    Planet::Planet(char* name, int diameter, bool has_life, int satellites) {
        this->name = new char[strlen(name) + 1];
        std::strncpy(this->name, name, strlen(name) + 1);

        this->diameter = diameter;
        this->has_life = has_life;
        this->satellites = satellites;
    }

    Planet::~Planet() = default;

    // Print
    std::ostream& operator<<(std::ostream& s, const Planet* p) {
        if (!p) {
            return s;
        }

        s << "Планета: " << p->name << ", Диаметр: " << p->diameter
          << ", Жизнь: " << p->has_life << ", Спутники: " << p->satellites
          << std::endl;

        return s;
    }

    std::istream& operator>>(std::istream& s, Planet*& p) {
        auto planet = db::Db::GetPlanetOnce(s);

        p->~Planet();
        if (!planet) {
            // std::cout << "Error reading planet." << std::endl;
            delete planet;
            p = nullptr;
            return s;
        }

        *p = Planet(const_cast<char*>(planet->name.c_str()), planet->diameter,
                    planet->has_life, planet->satellites);

        delete planet;
        return s;
    }
}  // namespace planets
