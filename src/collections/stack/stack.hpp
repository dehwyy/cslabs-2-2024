#pragma once

namespace stack {
    template <typename T, class Friend>
    class Node {
        private:
            T value = {};
            Node* next = nullptr;

            Node() = default;
            friend Friend;
    };

    template <typename T>
    class Stack {
        private:
            Node<T, Stack<T>>* top = nullptr;
            int size = 0;

        public:
            Stack() = default;
            Stack(const Stack& stack) {
                auto buf = new T[stack.size];
                Node<T, Stack<T>>* node = stack.top;

                for (int i = stack.size - 1; i >= 0; --i) {
                    buf[i] = node->value;
                    node = node->next;
                }

                for (int i = 0; i < stack.size; ++i) {
                    this->push(buf[i]);
                }

                delete[] buf;
            }
            ~Stack() = default;
            bool is_empty() { return top == nullptr; }
            void push(T value) {
                auto node = new Node<T, Stack<T>>();
                node->value = value;
                node->next = top;
                top = node;

                this->size++;
            }

            T pop() {
                T value = top->value;
                Node<T, Stack<T>>* node = top;
                top = top->next;
                delete node;

                this->size--;
                return value;
            }

            void reverse() {
                Node<T, Stack<T>>* node = top;
                Node<T, Stack<T>>* prev = nullptr;

                while (node != nullptr) {
                    Node<T, Stack<T>>* next = node->next;
                    node->next = prev;
                    prev = node;
                    node = next;
                }

                this->top = prev;
            }

            // `top_inf`
            T peek() const { return this->top->value; }

            int get_size() const { return this->size; }
    };
}  // namespace stack
