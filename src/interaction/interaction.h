#include <memory>
#include "../db/entity/entity.h"

namespace interaction {
    enum class EntityType { Planet = 1, Shop };
    EntityType ReadEntityInteractionType();
    std::unique_ptr<entity::PlanetEntity> ReadPlanetEntity();
    std::unique_ptr<entity::ShopEntity> ReadShopEntity();

    enum class DatabaseInteractionType {
        Insert = 1,
        Delete = 2,
        Sort = 3,
        SyncWithFile = 4,
        Print = 5,
        Stop = 6,
        SwitchTable = 7
    };
    DatabaseInteractionType ReadDatabaseInteractionType();
    int ReadEntityId();
}  // namespace interaction
