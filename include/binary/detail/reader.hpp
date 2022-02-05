#pragma once

#include <concepts> // std::same_as
#include <cstddef> // std::size_t
#include <string> // std::basic_string

#include "common.hpp"

namespace thr::binary::detail {
    template<typename InputAdapter, typename Byte>
    concept input_adapter = requires(InputAdapter adapter, Byte& byte, Byte* bytes, const std::size_t size) {
        { adapter.read(byte) } -> std::same_as<void>;
        { adapter.read(bytes, size) } -> std::same_as<void>;
    };

    template<typename Byte, input_adapter<Byte> InputAdapter>
    class reader {
        public:
            reader(InputAdapter&& adapter):
                input_adapter(std::forward<InputAdapter>(adapter)) {}

            template<numeric Number>
            void read(Number& number) {
                auto bytes = reinterpret_cast<Byte*>(&number);
                input_adapter.read(bytes, sizeof(Number));
            }

            template<class Char, class CharTraits, class Allocator>
            void read(std::basic_string<Char, CharTraits, Allocator>& string, const std::size_t size) {
                string.resize(size);
                auto bytes = reinterpret_cast<Byte*>(string.data());
                input_adapter.read(bytes, size * sizeof(Char));
            }

        private:
            InputAdapter input_adapter;
    };
} // namespace thr::binary::detail