#include "db.h"
#include <fstream>

namespace db {
    std::string Db::ReadOnce(std::istream& s) {
        if (s.eof()) {
            return "";
        }

        std::string line;
        std::getline(s, line);

        // if HEADER matches
        if (line == T_PLANETS) {
            std::getline(s, line);
        }

        return line;
    }

    SchemaPlanet* Db::ParsePlanet(std::string line) {
        // If doesn't start with [Planets]
        if (line.rfind("[" + T_PLANETS + "]", 0) != 0) {
            return nullptr;
        }

        line.erase(0, T_PLANETS.size() + 2);

        auto tokens = vec::Vector<std::string>();
        size_t pos = 0;
        std::string token = "";

        while ((pos = line.find(DELIM)) != std::string::npos) {
            token = line.substr(0, pos);
            token = token.substr(token.find("=") + 1);

            tokens.PushBack(token);
            line.erase(0, pos + DELIM.length());
        }
        if (line.length() > 0) {
            tokens.PushBack(line);
        }

        if (tokens.GetSize() != 5) {
            return nullptr;
        }

        auto p = new SchemaPlanet();

        p->name = tokens.Get(1);
        p->diameter = std::stoi(tokens.Get(2));
        p->has_life = std::stoi(tokens.Get(3));
        p->satellites = std::stoi(tokens.Get(4));

        return p;
    }

    SchemaPlanet* Db::GetPlanetOnce(std::istream& s) {
        std::string line = Db::ReadOnce(s);
        return Db::ParsePlanet(line);
    }

    std::ifstream Db::Open(std::string filepath) {
        std::ifstream f(filepath.c_str(),
                        std::ios::binary | std::ios::in | std::ios::out);
        return f;
    }
}  // namespace db
