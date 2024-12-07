#include <fstream>
#include <iostream>
#include <memory>
#include "db/db.h"
#include "db/tables/tables.h"
#include "planets/planets.h"

int main() {
    // auto s = db::Db::Open("db.db");
    // auto planet = new planets::Planet();
    // while (!s.eof()) {
    //     s >> planet;
    //     std::cout << planet;
    // }

    // delete planet;

    auto d = new db::Db2("db.db");
    auto planet = std::make_unique<tables::DbTablePlanets>();
    d->GetOne(*planet);

    auto pl = new planets::Planet(
        const_cast<char*>(planet->GetPlanetName().data()),
        planet->GetDiameter(), planet->HasLife(), planet->GetSatellites());

    std::cout << pl << std::endl;

    return 0;
}
