#pragma once

#include <ios> // std::streamsize
#include <istream> // std::basic_istream, std::basic_ostream
#include <memory> // std::addressof

//! @note Consider using streambufs instead using streams

namespace thr::binary::detail {
    template<typename Character, typename CharacterTraits>
    class StreamReader {
        private:
            using Stream = std::basic_istream<Character, CharacterTraits>;

        private:
            Stream& _stream;

        public:
            explicit StreamReader(Stream& stream):
                _stream(stream) {}

            void read(byte_t* p, const size_t size) {
                _stream.read(reinterpret_cast<char*>(p), static_cast<std::streamsize>(size));
            }
    };

    template<typename Character, typename CharacterTraits>
    class StreamWriter {
        private:
            using Stream = std::basic_ostream<Character, CharacterTraits>;

        private:
            Stream& _stream;

        public:
            explicit StreamWriter(Stream& stream):
                _stream(stream) {}

            void write(const byte_t* p, const size_t size) {
                _stream.write(reinterpret_cast<const char*>(p), static_cast<std::streamsize>(size));
            }
    };
} // namespace thr::binary