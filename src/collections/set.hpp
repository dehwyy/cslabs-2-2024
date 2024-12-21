#include <cstring>
#include <functional>
#include <memory>
#include "vector.hpp"

namespace {
    template <typename T>
    int compare(const T& left, const T& right) {
        return left - right;
    }

    template <>
    int compare(char* const& left, char* const& right) {
        return std::strcmp(left, right);
    }

    template <typename T>
    using CompareCallback = std::function<int(const T&, const T&)>;

    template <typename T>
    void quick_sort(T* data, int left, int right) {
        if (left >= right) {
            return;
        }

        T pivot = data[right];
        int i = left - 1;

        // Разделение массива
        for (int j = left; j < right; ++j) {
            // if (data[j] < pivot)
            if (compare(data[j], pivot) < 0) {
                ++i;
                std::swap(data[i], data[j]);
            }
        }

        std::swap(data[i + 1], data[right]);

        quick_sort(data, left, i);
        quick_sort(data, i + 2, right);
    }

    // Assume, that data is already sorted
    template <typename T>
    int binary_search(T* data, int left, int right, T value) {
        if (left > right) {
            return -1;
        }

        int mid = (left + right) / 2;
        if (compare(data[mid], value) == 0) {
            return mid;
        } else if (compare(data[mid], value) < 0) {
            return binary_search(data, mid + 1, right, value);
        } else {
            return binary_search(data, left, mid - 1, value);
        }
    }
}  // namespace

namespace set {
    template <typename T>
    class Set : public vector::Vec<T> {
        private:
            void q_sort() { quick_sort(this->data, 0, this->size - 1); }
            int q_find(T value) const { return binary_search(this->data, 0, this->size - 1, value); }
            // no sort, returns whether element was added
            bool q_add(T value) {
                if (this->has(value)) {
                    return false;
                }

                this->resize_grow_if_needed();
                this->data[this->size++] = value;

                return true;
            }

        public:
            bool has(T value) const { return this->q_find(value) != -1; }
            void add(T value) {
                if (this->q_add(value)) {
                    this->q_sort();
                }
            }

            void remove(T value) {
                if (this->has(value)) {
                    this->data[this->find(value)] = this->data[this->size - 1];
                    this->size--;
                }

                this->resize_shrink_if_needed();
                this->q_sort();
            }

            void operator-=(const Set<T>& other) { *this = *this - other; }

            void operator*=(const Set<T>& other) { *this = *this * other; }

            void operator+=(const Set<T>& other) { *this = *this + other; }

            friend Set<T> operator+(const Set<T>& left, const Set<T>& right) {
                Set<T> result;

                for (unsigned i = 0; i < left.size; ++i) {
                    result.q_add(left.data[i]);
                }
                for (unsigned i = 0; i < right.size; ++i) {
                    result.q_add(right.data[i]);
                }

                result.q_sort();

                return result;
            }

            friend Set<T> operator-(const Set<T>& left, const Set<T>& right) {
                Set<T> result;

                for (unsigned i = 0; i < left.size; ++i) {
                    if (!right.has(left.data[i])) {
                        result.q_add(left.data[i]);
                    }
                }

                result.q_sort();

                return result;
            }

            friend Set<T> operator*(const Set<T>& left, const Set<T>& right) {
                Set<T> result;

                for (unsigned i = 0; i < left.size; ++i) {
                    if (right.has(left.data[i])) {
                        result.q_add(left.data[i]);
                    }
                }

                result.q_sort();

                return result;
            }

            template <typename Friend>
            friend std::ostream& operator<<(std::ostream& out, const Set<Friend>& set);

            template <typename Friend>
            friend std::istream& operator>>(std::istream& is, Set<Friend>& set);
    };

    template <typename Friend>
    inline std::ostream& operator<<(std::ostream& out, const Set<Friend>& set) {
        out << "{";
        for (int i = 0; i < set.get_size(); ++i) {
            out << set.data[i];
            if (i != set.get_size() - 1) {
                out << ", ";
            }
        }
        out << "}";
        return out;
    }

    template <typename Friend>
    inline std::istream& operator>>(std::istream& is, Set<Friend>& set) {
        Friend value;
        while (is >> value) {
            set.add(value);
        }
        return is;
    }

    template <>
    inline std::istream& operator>>(std::istream& is, Set<char*>& set) {
        auto buffer = new char[1024];
        is.getline(buffer, 1024);

        set.add(buffer);

        char* token = std::strtok(buffer, " ");

        while (token != nullptr) {
            set.add(token);
            token = std::strtok(nullptr, " ");
        }

        return is;
    }
}  // namespace set
