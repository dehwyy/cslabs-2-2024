#pragma once

namespace {
    unsigned DEFAULT_CAPACITY = 16;
    unsigned GROWTH_FACTOR = 2;
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
            ~Vec() {
                if (this->data) {
                    for (unsigned i = 0; i < this->_size; ++i) {
                        delete this->data[i];
                    }
                }
            }

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

            void clear() {
                this->~Vec();
                this->_size = 0;
                this->capacity = DEFAULT_CAPACITY;
            }

            void print() const {
                for (unsigned i = 0; i < this->_size; ++i) {
                    std::cout << this->data[i] << std::endl;
                }
            }

            int size() const { return this->_size; }

            T& operator[](int index) const { return this->data[index]; }
    };
}  // namespace vector
