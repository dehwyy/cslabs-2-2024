#include "fraction.hpp"
#include <cmath>
#include <cstring>
#include <iostream>
#include <tuple>

namespace {
    const char SPACE = ' ';
    const char MINUS = '-';
    const char FRACTION_DELIM = '/';
    const int MAX_INPUT_LEN = 40;
    const int N_PRECISION = 4;

    std::tuple<int, int> from_double(double number) {
        int factor = std::pow(10, N_PRECISION);
        return std::make_tuple(static_cast<int>(number * factor), factor);
    }

    int greatest_common_divisor(int a, int b) {
        a = std::abs(a);
        b = std::abs(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    fraction::Fraction ParseInput(char* input) {
        // size_t size = std::strlen(input);
        size_t pos = 0;
        int integer = 0;
        int numerator = 0;
        int denominator = -1;

        // Пропускаем пробелы
        while (input[pos] == SPACE) {
            ++pos;
        }

        bool isMinus = false;
        if (input[pos] == MINUS) {
            isMinus = true;
            ++pos;
        }

        while (std::isdigit(input[pos])) {
            numerator = numerator * 10 + (input[pos] - '0');
            ++pos;
        }
        if (isMinus) {
            numerator = -numerator;
        }

        if (input[pos] == SPACE) {
            ++pos;
        }

        // Если есть дробная часть
        if (std::isdigit(input[pos])) {
            integer = numerator;
            numerator = 0;
        }
        while (std::isdigit(input[pos])) {
            numerator = numerator * 10 + (input[pos] - '0');
            ++pos;
        }

        if (input[pos] == FRACTION_DELIM) {
            ++pos;  // Пропускаем слэш
            denominator = 0;
            while (std::isdigit(input[pos])) {
                denominator = denominator * 10 + (input[pos] - '0');
                ++pos;
            }
        }

        // Представлена только целая часть
        if (denominator == -1) {
            integer = numerator;
            numerator = 0;
            denominator = 1;
        }

        // Проверка на некорректные дроби (например, знаменатель 0)
        if (denominator == 0) {
            std::cout << "Detected division by zero" << std::endl;
            exit(1);
        }

        auto instance = fraction::Fraction(integer, numerator, denominator);
        return instance;
    }
}  // namespace

namespace fraction {
    Fraction::Fraction(int integer, int numerator, int denominator) {
        if (denominator == 0) {
            std::cout << "Detected division by zero" << std::endl;
            exit(1);
        }

        this->integer = integer;
        this->numerator = numerator;
        this->denominator = denominator;
    }

    Fraction::Fraction(int numerator, int denominator) {
        this->integer = 0;
        this->numerator = numerator;
        this->denominator = denominator;
    }

    Fraction::Fraction(char* input) {
        auto parsedFraction = ParseInput(input);

        this->integer = parsedFraction.integer;
        this->numerator = parsedFraction.numerator;
        this->denominator = parsedFraction.denominator;
    }

    Fraction::Fraction(double number) {
        auto tuple = from_double(number);

        this->numerator = std::get<0>(tuple);
        this->denominator = std::get<1>(tuple);

        this->simplify();
    }

    void Fraction::simplify() {
        if (this->numerator == 0) {
            this->denominator = 1;
            return;
        }

        int gcd = greatest_common_divisor(this->numerator, this->denominator);

        this->numerator /= gcd;
        this->denominator /= gcd;

        bool isMinus = (this->integer < 0) ^ (this->numerator < 0);
        this->numerator = std::abs(this->numerator);
        // Нормализация дроби
        if (this->numerator >= this->denominator) {
            int integerDelta = this->numerator / this->denominator;
            this->integer += isMinus ? -integerDelta : integerDelta;

            this->numerator %= this->denominator;
        }
    }

    Fraction Fraction::operator+(const Fraction& other) const {
        int numerator = this->numerator * other.denominator + this->denominator * other.numerator;
        int denominator = this->denominator * other.denominator;

        auto instance = Fraction(this->integer + other.integer, numerator, denominator);
        instance.simplify();

        return instance;
    }

    Fraction Fraction::operator+(double number) const {
        return *this + Fraction(number);
    }
    Fraction Fraction::operator+(int number) const {
        return *this + Fraction(number);
    }

    void Fraction::operator+=(const Fraction& other) {
        *this = *this + other;
    }

    void Fraction::operator+=(double number) {
        *this += Fraction(number);
    }

    Fraction operator+(double number, const Fraction& other) {
        return other + number;
    }

    Fraction operator+(int number, const Fraction& other) {
        return other + number;
    }

    std::istream& operator>>(std::istream& s, Fraction& f) {
        char input[MAX_INPUT_LEN];

        s.getline(input, MAX_INPUT_LEN);

        f = ParseInput(input);

        return s;
    }

    std::ostream& operator<<(std::ostream& s, Fraction& f) {
        f.simplify();

        if ((f.integer < 0) ^ (f.numerator < 0)) {
            s << MINUS;
        }

        if (f.integer != 0) {
            s << std::abs(f.integer);
        }

        if (f.numerator != 0) {
            if (f.integer != 0) {
                s << SPACE;
            }
            s << std::abs(f.numerator) << FRACTION_DELIM << std::abs(f.denominator);
        }

        if (f.integer == 0 && f.numerator == 0) {
            s << "0";
        }

        std::cout << std::endl;

        return s;
    }
}  // namespace fraction
