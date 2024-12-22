#pragma once

namespace {
    unsigned DEFAULT_CAPACITY = 16;
    unsigned GROWTH_FACTOR = 2;

    template <typename T>
    void quick_sort(T* data, int left, int right, bool ascending) {
        if (left >= right) {
            return;
        }

        T pivot = data[right];
        int i = left - 1;

        // Array partition.
        for (int j = left; j < right; ++j) {
            if (ascending ? (data[j] < pivot) : !(data[j] < pivot)) {
                ++i;
                std::swap(data[i], data[j]);
            }
        }

        std::swap(data[i + 1], data[right]);

        quick_sort(data, left, i, ascending);
        quick_sort(data, i + 2, right, ascending);
    }

    // Assume, that data is already sorted.
    template <typename T>
    int _binary_search(T* data, int left, int right, T value, bool ascending) {
        if (left > right) {
            return -1;
        }

        int mid = (left + right) / 2;

        // If matches.
        if (data[mid] == value) {
            return mid;
        }

        // Left side.
        if (ascending ? (data[mid] < value) : !(data[mid] < value)) {
            return _binary_search(data, mid + 1, right, value, ascending);
        }

        // Right side.
        return _binary_search(data, left, mid - 1, value, ascending);
    }
}  // namespace

namespace vector {
    template <typename T>
    class Vec {
        protected:
            unsigned _size = 0;
            unsigned capacity = 0;
            T* data = nullptr;

            void resize() {
                if (this->_size < this->capacity) {
                    return;
                }

                this->capacity *= GROWTH_FACTOR;
                T* new_data = new T[this->capacity];
                for (unsigned i = 0; i < this->_size; ++i) {
                    new_data[i] = this->data[i];
                }
                delete[] this->data;
                this->data = new_data;
            }

        public:
            Vec() {
                this->data = new T[DEFAULT_CAPACITY];
                this->capacity = DEFAULT_CAPACITY;
            }
            Vec(const Vec& vector) {
                this->_size = vector.size();
                this->capacity = vector.capacity;
                this->data = new T[this->capacity];

                for (unsigned i = 0; i < this->_size; ++i) {
                    this->data[i] = vector.data[i];
                }
            }
            Vec& operator=(const Vec& other) {
                delete[] this->data;
                this->_size = other.size();
                this->data = new T[this->_size];
                std::copy(other.data, other.data + this->_size, this->data);
                return *this;
            }
            ~Vec() { delete[] this->data; }

            void push_back(T value) {
                this->resize();
                this->data[this->_size++] = value;
            }

            void remove(int index) {
                for (unsigned i = index; i < this->_size - 1; ++i) {
                    this->data[i] = this->data[i + 1];
                }
                this->_size--;
            }

            void remove(T value) {
                for (unsigned i = 0; i < this->_size; ++i) {
                    if (this->data[i] == value) {
                        this->remove(i);
                        break;
                    }
                }
            }
            int binary_search(T value, bool ascending = true) const {
                return _binary_search(this->data, 0, this->_size - 1, value, ascending);
            }
            void sort(bool ascending = true) { quick_sort(this->data, 0, this->_size - 1, ascending); }

            int size() const { return this->_size; }

            T& operator[](int index) const { return this->data[index]; }
    };
}  // namespace vector
