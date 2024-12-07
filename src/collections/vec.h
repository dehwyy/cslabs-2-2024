#pragma once
#include <cstddef>

namespace {
    size_t DEFAULT_CAPACITY = 10;
    char GROWTH_FACTOR = 2;
}  // namespace

namespace vec {
    template <typename T>
    class Vector {
        private:
            T* data = nullptr;
            size_t size = 0;
            size_t capacity = 0;

            void resize() {
                T* new_data = new T[this->capacity * 2];

                for (size_t i = 0; i < this->size; i++) {
                    new_data[i] = this->data[i];
                }
                delete[] this->data;

                this->data = new_data;
                this->capacity *= GROWTH_FACTOR;
            }

        public:
            Vector(size_t capacity = DEFAULT_CAPACITY) {
                this->capacity = capacity;
                this->data = new T[this->capacity];
            }
            ~Vector() {
                this->size = 0;
                this->capacity = 0;
                delete[] this->data;
            }

            size_t GetSize() const { return this->size; }

            T Get(size_t index) { return this->data[index]; }

            void PushBack(T value) {
                if (this->size == this->capacity) {
                    this->resize();
                }

                this->data[this->size++] = value;
            }
    };
}  // namespace vec
