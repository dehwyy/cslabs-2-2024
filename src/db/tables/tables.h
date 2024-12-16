#pragma once

#include <memory>
#include <string>
#include "../entity/entity.h"
#include "table_name.h"
#include "vector"

namespace tables {
    class DbTable {
        private:
            std::vector<std::unique_ptr<entity::Entity>> entities = {};

        public:
            std::vector<std::unique_ptr<entity::Entity>>& GetEntities();

            void AddEntity(std::unique_ptr<entity::Entity> entity);
            void RemoveEntity(int id);
            void Sort();
    };

}  // namespace tables
