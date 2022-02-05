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
    template<typename InputAdapter>
    class reader: public detail::reader<std::byte, InputAdapter> {
        public:
            reader(InputAdapter&& adapter):
                detail::reader<std::byte, InputAdapter>(std::forward<InputAdapter>(adapter)) {}
    };

    template<typename OutputAdapter>
    class writer: public detail::writer<std::byte, OutputAdapter> {
        public:
            writer(OutputAdapter&& adapter):
                detail::writer<std::byte, OutputAdapter>(std::forward<OutputAdapter>(adapter)) {}
    };

    // Input adapter factories
    template<std::input_iterator Iterator, std::sentinel_for<Iterator> Sentinel>
    detail::input_iterator_adapter<std::byte, Iterator, Sentinel>
    input_adapter(Iterator iterator, Sentinel sentinel) {
        return {iterator, sentinel};
    }

    template<std::ranges::input_range Range>
    detail::input_iterator_adapter<std::byte, std::ranges::iterator_t<Range>, std::ranges::sentinel_t<Range>>
    input_adapter(Range& range) {
        return {std::ranges::begin(range), std::ranges::end(range)};
    }

    template<typename Char, typename CharTraits>
    detail::input_stream_adapter<std::byte, Char, CharTraits>
    input_adapter(std::basic_istream<Char, CharTraits>& stream) {
        return {stream};
    }

    // Output adapter factories
    template<std::output_iterator<std::byte> Iterator>
    detail::output_iterator_adapter<std::byte, Iterator>
    output_adapter(Iterator iterator) {
        return {iterator};
    }

    template<typename Char, typename CharTraits>
    detail::output_stream_adapter<std::byte, Char, CharTraits>
    output_adapter(std::basic_ostream<Char, CharTraits>& stream) {
        return {stream};
    }
} // namespace thr::binary