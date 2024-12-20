#include "tables.h"
#include <algorithm>
#include <iostream>

namespace tables {
    std::vector<std::unique_ptr<entity::Entity>>& DbTable::GetEntities() {
        return this->entities;
    }

    void DbTable::AddEntity(std::unique_ptr<entity::Entity> entity) {
        this->entities.push_back(std::move(entity));
    }

    void DbTable::RemoveEntity(int id) {
        for (size_t i = 0; i < this->entities.size(); i++) {
            if (this->entities.at(i).get()->GetId() == id) {
                this->entities.erase(this->entities.begin() + i);
                return;
            }
        }
    }

    void DbTable::Sort() {
        std::sort(this->entities.begin(),
                  this->entities.end(),
                  [](std::unique_ptr<entity::Entity>& a, std::unique_ptr<entity::Entity>& b) {
                      return *a.get() < *b.get();
                  });
    }
}  // namespace tables
