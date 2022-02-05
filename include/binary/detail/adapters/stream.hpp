#pragma once

#include <cstddef> // std::size_t
#include <ios> // std::streamsize
#include <istream> // std::basic_istream
#include <ostream> // std::basic_ostream

namespace thr::binary::detail {
    template<typename Byte, typename Char, typename CharTraits>
    class output_stream_adapter {
        public:
            using output_stream_type = std::basic_ostream<Char, CharTraits>;

            output_stream_adapter(output_stream_type& stream):
                stream(stream) {}

            void write(const Byte byte) {
                stream.write(reinterpret_cast<const Char*>(&byte), 1);
            }

            void write(const Byte* bytes, const std::size_t size) {
                stream.write(reinterpret_cast<const Char*>(bytes), static_cast<std::streamsize>(size));
            }

        private:
            output_stream_type& stream;
    };

    template<typename Byte, typename Char, typename CharTraits>
    class input_stream_adapter {
        public:
            using input_stream_type = std::basic_istream<Char, CharTraits>;

            input_stream_adapter(input_stream_type& stream):
                stream(stream) {}

            void read(Byte& byte) {
                stream.read(reinterpret_cast<Char*>(&byte), 1);
            }

            void read(Byte* p, const std::size_t size) {
                stream.read(reinterpret_cast<Char*>(p), static_cast<std::streamsize>(size));
            }

        private:
            input_stream_type& stream;
    };
}; // namespace thr::binary::detail
