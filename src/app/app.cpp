#include "app.hpp"
#include <iostream>
#include "../collections/vector.hpp"
#include "../state/state.hpp"

namespace app {
    void RunDemo() {
        vector::Vec<state::State*> states = {};
        states.push_back(
            new state::Republic((char*)"Россия", 143000000, 446000, (char*)"Владимир Путин", 4));

        states.push_back(new state::Monarchy((char*)"Казахстан",
                                             18000000,
                                             466000,
                                             (char*)"Нурсултан Назарбаев",
                                             (char*)"Казахстанская монархия"));

        states.push_back(new state::Kingdom(
            (char*)"Турция", 80000000, 780000, (char*)"Эрдоган", (char*)"Королевство", (char*)"Ислам"));

        states.push_back(new state::Republic(
            (char*)"Индия", 1300000000, 3280000, (char*)"Народная республика Индия", 4));

        for (int i = 0; i < states.size(); i++) {
            states[i]->show();
        }
    }

    void RunInteractive() {}
}  // namespace app
