#pragma once

#include <memory> // std::addressof
#include <string> // std::basic_string

#include "concepts.hpp"
#include "types.hpp"

namespace thr::binary::detail {
    template<writer_adapter Adapter>
    class Writer {
        private:
            Adapter _adapter;

        public:
            Writer(Adapter a):
                _adapter(a) {}

            void write(const byte_t& b) {
                _adapter.write(std::addressof(b), 1);
            }

            template<numeric T>
            void write(const T& value) {
                _adapter.write(reinterpret_cast<const byte_t*>(std::addressof(value)), sizeof(T));
            }

            //! @todo Write nulls when string.size() < size
            //! @todo Forwarding
            template<class Character, class CharacterTraits, class Allocator>
            void write(const std::basic_string<Character, CharacterTraits, Allocator>& string, const size_t size) {
                _adapter.write(reinterpret_cast<const byte_t*>(string.data()), size * sizeof(Character));
            }

            template<class Character, class CharacterTraits, class Allocator>
            void write(const std::basic_string<Character, CharacterTraits, Allocator>& string) {
                write(string, string.size());
            }
    };
} // namespace thr::binary