#pragma once

#include <memory>
#include "../entity/entity.h"

namespace serde {

    class Deserializer {
        public:
            static std::unique_ptr<entity::Entity> FromString(std::string s);
    };

    class Serializer {
        public:
            static std::string Serialize(entity::Entity& entity);
            static std::string Pretty(entity::Entity& entity);
    };
}  // namespace serde
