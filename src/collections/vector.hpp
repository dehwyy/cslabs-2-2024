namespace {
    unsigned DEFAULT_CAPACITY = 16;
    unsigned GROWTH_FACTOR = 2;
    unsigned SHRINK_FACTOR = 4;
}  // namespace

namespace vector {
    template <typename T>
    class Vec {
        protected:
            unsigned size = 0;
            unsigned capacity = 0;
            T* data = nullptr;

            void resize_grow_if_needed() {
                if (this->size < this->capacity) {
                    return;
                }

                this->capacity *= GROWTH_FACTOR;
                T* new_data = new T[this->capacity];
                for (unsigned i = 0; i < this->size; ++i) {
                    new_data[i] = this->data[i];
                }
                delete[] this->data;
                this->data = new_data;
            }

            void resize_shrink_if_needed() {
                if (this->size >= this->capacity / SHRINK_FACTOR) {
                    return;
                }

                this->capacity /= GROWTH_FACTOR;
                T* new_data = new T[this->capacity];
                for (unsigned i = 0; i < this->size; ++i) {
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
                this->size = vector.size;
                this->capacity = vector.capacity;
                this->data = new T[this->capacity];

                for (unsigned i = 0; i < this->size; ++i) {
                    this->data[i] = vector.data[i];
                }
            }
            ~Vec() { delete[] this->data; }

            void add(T value) {
                this->resize_grow_if_needed();
                this->data[this->size++] = value;
            }

            void remove(T value) {
                for (unsigned i = 0; i < this->size; ++i) {
                    if (this->data[i] == value) {
                        this->data[i] = this->data[this->size - 1];
                        this->size--;
                        break;
                    }
                }

                this->resize_shrink_if_needed();
            }

            int find(T value) {
                for (unsigned i = 0; i < this->size; ++i) {
                    if (this->data[i] == value) {
                        return i;
                    }
                }
                return -1;
            }

            int get_size() const { return this->size; }

            T& operator[](int index) { return this->data[index]; }
    };
}  // namespace vector
