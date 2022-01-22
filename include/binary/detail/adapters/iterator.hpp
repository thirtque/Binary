#pragma once

#include <concepts> // std::same_as
#include <iterator> // std::input_iterator, std::output_iterator, std::sentinel_for, std::iterator_traits

#include "../reader.hpp"
#include "../types.hpp"
#include "../writer.hpp"

namespace thr::binary::detail {
    template<std::input_iterator Iterator, std::sentinel_for<Iterator> Sentinel>
    class IteratorReader {
        private:
            using IteratorValue = typename std::iterator_traits<Iterator>::value_type;

        private:
            Iterator _iterator;
            Sentinel _sentinel;

        public:
            IteratorReader(Iterator iterator, Sentinel sentinel):
                _iterator(iterator),
                _sentinel(sentinel) {}

            void read(byte_t* p, const size_t size) {
                for (size_t i = 0; i < size && _iterator != _sentinel; ++i) {
                    auto ip = reinterpret_cast<byte_t*>(_iterator);
                    for (size_t j = 0; j < sizeof(IteratorValue); j++) {
                        *p = *ip;
                        ++p;
                        ++ip;
                    }
                    ++_iterator;
                }
            }
    };

    template<typename IteratorValue, std::output_iterator<IteratorValue> Iterator>
    class IteratorWriter {
        private:
            Iterator _iterator;

        public:
            IteratorWriter(Iterator iterator):
                _iterator(iterator){};

            void write(const byte_t* p, const size_t size) {
                for (size_t i = 0; i < size; ++i) {
                    auto ip = reinterpret_cast<byte_t*>(_iterator);
                    for (size_t j = 0; j < sizeof(IteratorValue); j++) {
                        *ip = *p;
                        ++p;
                        ++ip;
                    }
                    ++_iterator;
                }
            }
    };
} // namespace thr::binary::detail::adapter