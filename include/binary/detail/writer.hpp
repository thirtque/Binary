#pragma once

#include <algorithm> // std::min
#include <concepts> // std::same_as
#include <cstddef> // std::size_t
#include <string> // std::basic_string

namespace thr::binary::detail {
    template<typename OutputAdapter, typename Byte>
    concept output_adapter = requires(OutputAdapter adapter, const Byte byte, const Byte* bytes, const std::size_t size) {
        { adapter.write(byte) } -> std::same_as<void>;
        { adapter.write(bytes, size) } -> std::same_as<void>;
    };

    template<typename Byte, output_adapter<Byte> OutputAdapter>
    class BasicWriter {
        private:
            OutputAdapter _adapter;

        public:
            BasicWriter(OutputAdapter&& adapter):
                _adapter(std::forward<OutputAdapter>(adapter)) {}

            template<typename Number>
            void write(const Number& number) {
                auto bytes = reinterpret_cast<const Byte*>(&number);
                _adapter.write(bytes, sizeof(Number));
            }

            template<class Char, class CharTraits, class Allocator>
            void write(const std::basic_string<Char, CharTraits, Allocator>& string, const std::size_t size) {
                auto bytes = reinterpret_cast<const Byte*>(string.data());
                _adapter.write(bytes, std::min(size, string.size()) * sizeof(Char));
                // Pad remaining bytes with \0
                for (auto i = string.size(); i < size; ++i) {
                    _adapter.write(Byte{0});
                }
            }

            template<class Char, class CharTraits, class Allocator>
            void write(const std::basic_string<Char, CharTraits, Allocator>& string) {
                write(string, string.size());
            }
    };
} // namespace thr::binary::detail