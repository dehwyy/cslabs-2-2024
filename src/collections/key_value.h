#pragma once
#include <string>

namespace key_value {
    class KeyValue {
        public:
            KeyValue(std::string s, char delim) {
                size_t pos = s.find(delim);
                this->key = s.substr(0, pos);
                this->value = s.substr(pos + 1);
            }
            std::string GetKey() const { return key; }
            std::string GetValue() const { return value; }

        private:
            std::string key = {};
            std::string value = {};
    };
}  // namespace key_value
