#include <iostream>
#include "../db/db.h"

namespace planets {
    class Planet {
        private:
            char* name = nullptr;
            int diameter = 0;
            bool has_life = false;
            int satellites = 0;

        public:
            Planet();
            Planet(char* name, int diameter, bool has_life, int satellites);
            ~Planet();

            friend std::istream& operator>>(std::istream& s, Planet*& p);
            friend std::ostream& operator<<(std::ostream& s, const Planet* p);
    };
}  // namespace planets
