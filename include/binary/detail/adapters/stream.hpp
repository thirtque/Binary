#pragma once

#include <cstddef> // std::size_t
#include <ios> // std::streamsize
#include <istream> // std::basic_istream
#include <ostream> // std::basic_ostream

namespace thr::binary::detail {
    template<typename Byte, typename Char, typename CharTraits>
    class OutputStreamAdapter {
        public:
            using OutputStreamType = std::basic_ostream<Char, CharTraits>;

        private:
            OutputStreamType& _stream;

        public:
            OutputStreamAdapter(OutputStreamType& stream):
                _stream(stream) {}

            void write(const Byte byte) {
                _stream.write(reinterpret_cast<const Char*>(&byte), 1);
            }

            void write(const Byte* bytes, const std::size_t size) {
                _stream.write(reinterpret_cast<const Char*>(bytes), static_cast<std::streamsize>(size));
            }
    };

    template<typename Byte, typename Char, typename CharTraits>
    class InputStreamAdapter {
        public:
            using InputStreamType = std::basic_istream<Char, CharTraits>;

        private:
            InputStreamType& _stream;

        public:
            InputStreamAdapter(InputStreamType& stream):
                _stream(stream) {}

            void read(Byte& byte) {
                _stream.read(reinterpret_cast<Char*>(&byte), 1);
            }

            void read(Byte* p, const std::size_t size) {
                _stream.read(reinterpret_cast<Char*>(p), static_cast<std::streamsize>(size));
            }
    };
}; // namespace thr::binary::detail
