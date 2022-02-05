#pragma once

#include <algorithm> // std::for_each_n
#include <cassert> // assert
#include <cstddef> // std::size_t
#include <iterator> // std::output_iterator, std::input_iterator, std::sentinel_for, std::iter_value_t

namespace thr::binary::detail {
    template<typename T>
    concept single_byte = sizeof(T) == 1;

    template<typename Byte, std::output_iterator<Byte> Iterator>
    class output_iterator_adapter {
        public:
            output_iterator_adapter(Iterator iterator):
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

        private:
            Iterator _iterator;
    };

    template<typename Byte, std::input_iterator Iterator, std::sentinel_for<Iterator> Sentinel>
    class input_iterator_adapter {
        public:
            using iterator_value_type = typename std::iter_value_t<Iterator>;

            input_iterator_adapter(Iterator iterator, Sentinel sentinel):
                iterator(iterator),
                sentinel(sentinel) {}

            void read(Byte& byte) {
                assert(iterator != sentinel && "Iterator has reached last value");

                read_impl<iterator_value_type>(byte);
            }

            void read(Byte* bytes, const std::size_t size) {
                std::for_each_n(bytes, size, [&](Byte& byte) {
                    read(byte);
                });
            }

        private:
            Iterator iterator;
            Sentinel sentinel;

            std::size_t value_iterator = 0;

            template<single_byte T>
            void read_impl(Byte& byte) {
                byte = static_cast<Byte>(*iterator);
                ++iterator;
            }

            template<typename T>
            requires(!single_byte<T>) void read_impl(Byte& byte) {
                auto iteratorPointer = reinterpret_cast<Byte*>(&(*iterator));
                byte = static_cast<Byte>(*(iteratorPointer + value_iterator));
                ++value_iterator;
                if (value_iterator >= sizeof(T)) {
                    ++iterator;
                    value_iterator = 0;
                }
            }
    };
}; // namespace thr::binary::detail
