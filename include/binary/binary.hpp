#pragma once

#include <cstddef> // std::byte
#include <istream> // std::basic_istream
#include <iterator> // std::input_iterator, std::sentinel_for, std::output_iterator
#include <ostream> // std::basic_ostream
#include <ranges> // std::ranges::input_range, std::ranges::begin, std::ranges::end

#include "detail/adapters/iterator.hpp"
#include "detail/adapters/stream.hpp"
#include "detail/reader.hpp"
#include "detail/writer.hpp"

namespace thr::binary {
    template<detail::input_adapter<std::byte> InputAdapter>
    using Reader = detail::BasicReader<std::byte, InputAdapter>;

    template<detail::output_adapter<std::byte> OutputAdapter>
    using Writer = detail::BasicWriter<std::byte, OutputAdapter>;

    template<typename Iterator, typename Sentinel>
    using InputIteratorAdapter = detail::InputIteratorAdapter<std::byte, Iterator, Sentinel>;

    template<typename Iterator>
    using OutputIteratorAdapter = detail::OutputIteratorAdapter<std::byte, Iterator>;

    template<typename Char, typename CharTraits>
    using InputStreamAdapter = detail::InputStreamAdapter<std::byte, Char, CharTraits>;

    template<typename Char, typename CharTraits>
    using OutputStreamAdapter = detail::OutputStreamAdapter<std::byte, Char, CharTraits>;

    // Iterator
    template<std::input_iterator Iterator, std::sentinel_for<Iterator> Sentinel>
    auto reader(Iterator iterator, Sentinel sentinel) {
        using Adapter = InputIteratorAdapter<Iterator, Sentinel>;

        return Reader<Adapter>(Adapter(iterator, sentinel));
    }

    template<std::output_iterator<std::byte> Iterator>
    auto writer(Iterator iterator) {
        using Adapter = OutputIteratorAdapter<Iterator>;

        return Writer<Adapter>(Adapter(iterator));
    }

    // Range
    template<std::ranges::input_range Range>
    auto reader(Range& range) {
        return reader(std::ranges::begin(range), std::ranges::end(range));
    }

    // Stream
    template<typename Char, typename CharTraits>
    auto reader(std::basic_istream<Char, CharTraits>& stream) {
        using Adapter = InputStreamAdapter<Char, CharTraits>;

        return Reader<Adapter>(Adapter(stream));
    }

    template<typename Char, typename CharTraits>
    auto writer(std::basic_ostream<Char, CharTraits>& stream) {
        using Adapter = OutputStreamAdapter<Char, CharTraits>;

        return Writer<Adapter>(Adapter(stream));
    }
} // namespace thr::binary