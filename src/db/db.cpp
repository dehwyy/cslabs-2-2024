#include "db.h"

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

    void Db2::InitDbIndexes() {
        std::string s = "";
        while (!this->index_file_handle.eof()) {
            std::getline(this->index_file_handle, s);

            auto kv = key_value::KeyValue(s, this->KEY_VALUE_DELIM);

            bool matches = false;
            if (kv.GetKey() == tables::DbTablePlanetsName ||
                kv.GetKey() == tables::DbTableShopName) {
                matches = true;
            }

            if (matches) {
                this->tables[kv.GetKey()] = std::stoi(kv.GetValue());
            }
        }

        this->index_file_handle.clear();
        this->index_file_handle.seekg(0, std::ios::beg);
    }

    void Db2::RemovePrefix(std::string& line) {
        line = line.substr(line.find(this->PREFIX_DELIM) + 1);
    }

    Db2::Db2(std::string filepath) {
        auto flags = std::ios::binary | std::ios::in | std::ios::out;

        this->filepath = filepath;
        this->file_handle.open(this->filepath.c_str(), flags);
        this->index_file_handle.open(this->INDEX_FILEPATH, flags);

        if (!this->file_handle.is_open()) {
            std::cerr << "Error opening db file." << std::endl;
        }

        if (!this->index_file_handle.is_open()) {
            std::cerr << "Error opening an index file." << std::endl;
        } else {
            this->InitDbIndexes();
        }
    }

    Db2::~Db2() {
        this->file_handle.close();
        this->index_file_handle.close();
    }

    void Db2::GetOne(tables::DbTable& table) {
        std::string line = "";
        for (unsigned i = 0; i < this->tables[table.GetName()]; i++) {
            std::getline(this->file_handle, line);
        }

        if (this->file_handle.eof()) {
            return;
        }

        std::getline(this->file_handle, line);
        this->RemovePrefix(line);

        table.Parse(line);

        this->file_handle.clear();
        this->file_handle.seekg(0, std::ios::beg);
    }

}  // namespace db
