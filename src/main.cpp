#include <fstream>
#include <iostream>
#include "db/db.h"
#include "planets/planets.h"

int main() {
    auto s = db::Db::Open("db.db");

    auto planet = new planets::Planet();
    while (!s.eof()) {
        s >> planet;
        std::cout << planet;
    }

    delete planet;

    return 0;
}
