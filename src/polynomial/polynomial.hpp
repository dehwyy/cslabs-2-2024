#pragma once
#include <iostream>
#include "../collections/vector.hpp"

namespace polynomial {
    namespace term {
        class Term {
            private:
                int coefficient = 0;
                int exponent = 0;
                friend class Polynomial;

            public:
                Term(int coefficient = 0, int exponent = 0);
                ~Term() = default;

                static Term parse(char*& el);
                void writeToStream(std::ostream& out, bool as_sequence = false) const;

                bool isZero() const;

                bool operator==(const Term& other) const;
                bool operator<(const Term& other) const;
                Term operator+(const Term& other) const;
                Term operator*(const Term& other) const;
                // Term operator*(const Term& other) const;

                friend std::ostream& operator<<(std::ostream& out, const Term& term);
                friend std::istream& operator>>(std::istream& is, Term& term);
        };
    }  // namespace term

    class Polynomial {
        private:
            vector::Vec<term::Term> poly = {};
            int exponent = 0;
            bool ascending = false;

        public:
            Polynomial() = default;
            Polynomial(int n);
            Polynomial(term::Term term);

            void operator+=(const Polynomial& other);
            void operator*=(const Polynomial& other);

            friend Polynomial operator+(const Polynomial& left, const Polynomial& right);
            friend Polynomial operator*(const Polynomial& left, const Polynomial& right);

            friend std::ostream& operator<<(std::ostream& out, const Polynomial& poly);
            friend std::istream& operator>>(std::istream& is, Polynomial& poly);
    };
}  // namespace polynomial
