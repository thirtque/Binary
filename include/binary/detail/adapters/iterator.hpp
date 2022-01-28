#pragma once

#include <algorithm> // std::for_each_n
#include <cassert> // assert
#include <cstddef> // std::size_t
#include <iterator> // std::output_iterator, std::input_iterator, std::sentinel_for, std::iter_value_t

namespace thr::binary::detail {
    template<typename T>
    concept single_byte = sizeof(T) == 1;

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
            using IteratorValue = typename std::iter_value_t<Iterator>;

        private:
            Iterator _iterator;
            Sentinel _sentinel;

            std::size_t _i = 0;

        private:
            template<single_byte T>
            void _read(Byte& byte) {
                byte = static_cast<Byte>(*_iterator);
                ++_iterator;
            }

            template<typename T>
            requires(!single_byte<T>)
            void _read(Byte& byte) {
                auto iteratorPointer = reinterpret_cast<Byte*>(&(*_iterator));
                byte = static_cast<Byte>(*(iteratorPointer + _i));
                ++_i;
                if (_i >= sizeof(T)) {
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

                _read<IteratorValue>(byte);
            }

            void read(Byte* bytes, const std::size_t size) {
                std::for_each_n(bytes, size, [&](Byte& byte) {
                    read(byte);
                });
            }
    };
}; // namespace thr::binary::detail
