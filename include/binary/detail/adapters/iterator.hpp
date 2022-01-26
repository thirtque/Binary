#pragma once

#include <algorithm> // std::for_each_n
#include <cassert> // assert
#include <cstddef> // std::size_t
#include <iterator> // std::output_iterator, std::input_iterator, std::sentinel_for, std::iterator_traits

namespace thr::binary::detail {
    template<typename Value>
    concept single_byte_size = sizeof(Value) == 1;

    template<typename Byte, std::output_iterator<Byte> Iterator>
    class OutputIteratorAdapter {
        private:
            Iterator _iterator;

        public:
            OutputIteratorAdapter(Iterator iterator):
                _iterator(iterator) {}

            void write(const Byte byte) {
                *_iterator = byte;
                ++_iterator;
            }

            void write(const Byte* bytes, const std::size_t size) {
                std::for_each_n(bytes, size, [&](const Byte& byte) {
                    write(byte);
                });
            }
    };

    template<typename Byte, std::input_iterator Iterator, std::sentinel_for<Iterator> Sentinel>
    class InputIteratorAdapter {
        private:
            Iterator _iterator;
            Sentinel _sentinel;

            std::size_t _i = 0;

        private:
            template<single_byte_size Value>
            void _readValue(Byte& byte) {
                byte = *_iterator;
                ++_iterator;
            }

            template<typename Value>
            requires(!single_byte_size<Value>) void _readValue(Byte& byte) {
                auto bytes = reinterpret_cast<Byte*>(&(*_iterator));
                byte = *(bytes + _i);
                ++_i;
                if (_i >= sizeof(Value)) {
                    ++_iterator;
                    _i = 0;
                }
            }

        public:
            InputIteratorAdapter(Iterator iterator, Sentinel sentinel):
                _iterator(iterator),
                _sentinel(sentinel) {}

            void read(Byte& byte) {
                assert(_iterator != _sentinel && "Iterator has reached last value");

                _readValue<typename std::iterator_traits<Iterator>::value_type>(byte);
            }

            void read(Byte* bytes, const std::size_t size) {
                std::for_each_n(bytes, size, [&](Byte& byte) {
                    read(byte);
                });
            }
    };
}; // namespace thr::binary::detail
