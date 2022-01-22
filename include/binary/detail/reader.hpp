#pragma once

#include <memory> // std::addressof
#include <string> // std::basic_string

#include "concepts.hpp"
#include "types.hpp"

namespace thr::binary::detail {
    template<reader_adapter Adapter>
    class Reader {
        private:
            Adapter _adapter;

        public:
            Reader(Adapter a):
                _adapter(a) {}

            void read(byte_t& b) {
                _adapter.read(std::addressof(b), 1);
            }

            template<numeric T>
            void read(T& value) {
                _adapter.read(reinterpret_cast<byte_t*>(std::addressof(value)), sizeof(T));
            }

            template<class Character, class CharacterTraits, class Allocator>
            void read(std::basic_string<Character, CharacterTraits, Allocator>& string, const size_t size) {
                string.resize(size);
                _adapter.read(reinterpret_cast<byte_t*>(string.data()), size * sizeof(Character));
            }
    };
} // namespace thr::binary