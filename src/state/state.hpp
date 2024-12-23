#pragma once
#include <iostream>

namespace state {
    class State {
        protected:
            char* name = {};
            int population;
            double area;
            char* governmentType;

        public:
            State(char* name, int population, double area, char* governmentType);
            virtual ~State();

            double calculateDensity() const;
            virtual void show() const = 0;

            friend std::ostream& operator<<(std::ostream& os, const State* state);
    };

    class Republic : public State {
        protected:
            char* president;
            int presidentTermLength;

        public:
            Republic(char* name, int population, double area, char* president, int presidentTermLength);
            ~Republic() override;

            void show() const override;
    };

    class Monarchy : public State {
        protected:
            char* monarch;
            char* monarchyType;

        public:
            Monarchy(char* name, int population, double area, char* monarch, char* monarchyType);
            ~Monarchy() override;

            void show() const override;
    };

    class Kingdom : public Monarchy {
        protected:
            char* mainReligion;

        public:
            Kingdom(char* name,
                    int population,
                    double area,
                    char* monarch,
                    char* monarchyType,
                    char* mainReligion);
            ~Kingdom() override;

            void show() const override;
    };
}  // namespace state
