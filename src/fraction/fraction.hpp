#pragma once
#include <fstream>

namespace fraction {
    class Fraction {
        private:
            int integer = 0;      // целая часть
            int numerator = 0;    // числитель
            int denominator = 1;  // знаменатель

            void simplify();

        public:
            Fraction(int integer, int numerator, int denominator);
            Fraction(int numerator = 0, int denominator = 1);
            Fraction(char* input);
            Fraction(double number);

            Fraction operator+(const Fraction& other) const;
            Fraction operator+(double number) const;
            Fraction operator+(int number) const;
            friend Fraction operator+(double number, const Fraction& other);
            friend Fraction operator+(int number, const Fraction& other);

            void operator+=(const Fraction& other);
            void operator+=(double number);

            friend std::istream& operator>>(std::istream& s, Fraction&);  // cin
            friend std::ostream& operator<<(std::ostream& s, Fraction&);  // cout
    };
}  // namespace fraction
