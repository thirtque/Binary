#pragma once

#include <concepts> // std::same_as
#include <cstddef> // std::size_t
#include <string> // std::basic_string

namespace thr::binary::detail {
    template<typename InputAdapter, typename Byte>
    concept input_adapter = requires(InputAdapter adapter, Byte& byte, Byte* bytes, const std::size_t size) {
        { adapter.read(byte) } -> std::same_as<void>;
        { adapter.read(bytes, size) } -> std::same_as<void>;
    };

    template<typename Byte, input_adapter<Byte> InputAdapter>
    class BasicReader {
        private:
            InputAdapter _adapter;

        public:
            BasicReader(InputAdapter&& adapter):
                _adapter(std::forward<InputAdapter>(adapter)) {}

            template<typename Number>
            void read(Number& number) {
                auto bytes = reinterpret_cast<Byte*>(&number);
                _adapter.read(bytes, sizeof(Number));
            }

            template<class Char, class CharTraits, class Allocator>
            void read(std::basic_string<Char, CharTraits, Allocator>& string, const std::size_t size) {
                string.resize(size);
                auto bytes = reinterpret_cast<Byte*>(string.data());
                _adapter.read(bytes, size * sizeof(Char));
            }
    };
} // namespace thr::binary::detail