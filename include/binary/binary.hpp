#pragma once

#include "detail/adapters/iterator.hpp"
#include "detail/adapters/range.hpp"
#include "detail/adapters/stream.hpp"
#include "detail/reader.hpp"
#include "detail/writer.hpp"

namespace thr::binary {
    // Iterators
    template<std::input_iterator Iterator, std::sentinel_for<Iterator> Sentinel>
    auto Reader(Iterator iterator, Sentinel sentinel) {
        return detail::Reader(detail::IteratorReader(iterator, sentinel));
    }

    template<std::output_iterator<detail::byte_t> Iterator>
    auto Writer(Iterator iterator) {
        return detail::Writer(detail::IteratorWriter<detail::byte_t, Iterator>(iterator));
    }

    // Streams
    template<typename Character, typename CharacterTraits>
    auto Writer(std::basic_ostream<Character, CharacterTraits>& stream) {
        return detail::Writer(detail::StreamWriter(stream));
    }

    template<typename Character, typename CharacterTraits>
    auto Reader(std::basic_istream<Character, CharacterTraits>& stream) {
        return detail::Reader(detail::StreamReader(stream));
    }
}