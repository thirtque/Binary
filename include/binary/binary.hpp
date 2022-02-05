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
    // Writer and output specialization
    template<std::output_iterator<std::byte> Iterator>
    using output_iterator_adapter = detail::output_iterator_adapter<std::byte, Iterator>;

    template<typename Char, typename CharTraits>
    using output_stream_adapter = detail::output_stream_adapter<std::byte, Char, CharTraits>;

    template<typename OutputAdapter>
    class writer: public detail::writer<std::byte, OutputAdapter> {
        public:
            writer(OutputAdapter&& adapter):
                detail::writer<std::byte, OutputAdapter>(std::forward<OutputAdapter>(adapter)) {}
    };

    template<std::output_iterator<std::byte> Iterator>
    writer<output_iterator_adapter<Iterator>>
    make_writer(Iterator iterator) {
        return {{iterator}};
    }

    template<typename Char, typename CharTraits>
    writer<output_stream_adapter<Char, CharTraits>>
    make_writer(std::basic_ostream<Char, CharTraits>& stream) {
        return {{stream}};
    }

    // region Reader and input specialization
    template<std::input_iterator Iterator, std::sentinel_for<Iterator> Sentinel>
    using input_iterator_adapter = detail::input_iterator_adapter<std::byte, Iterator, Sentinel>;

    template<typename Char, typename CharTraits>
    using input_stream_adapter = detail::input_stream_adapter<std::byte, Char, CharTraits>;

    template<typename InputAdapter>
    class reader: public detail::reader<std::byte, InputAdapter> {
        public:
            reader(InputAdapter&& adapter):
                detail::reader<std::byte, InputAdapter>(std::forward<InputAdapter>(adapter)) {}
    };

    template<std::input_iterator Iterator, std::sentinel_for<Iterator> Sentinel>
    reader<input_iterator_adapter<Iterator, Sentinel>>
    make_reader(Iterator iterator, Sentinel sentinel) {
        return {{iterator, sentinel}};
    }

    template<std::ranges::input_range Range>
    reader<input_iterator_adapter<std::ranges::iterator_t<Range>, std::ranges::sentinel_t<Range>>>
    make_reader(Range& range) {
        return {{std::ranges::begin(range), std::ranges::end(range)}};
    }

    template<typename Char, typename CharTraits>
    reader<input_stream_adapter<Char, CharTraits>>
    make_reader(std::basic_istream<Char, CharTraits>& stream) {
        return {{stream}};
    }
    // endregion
} // namespace thr::binary