#pragma once

#include <concepts> // std::integral, std::floating_point

#include "types.hpp"

namespace thr::binary::detail {
    template<typename T>
    concept numeric = std::integral<T> || std::floating_point<T>;

    template<typename ReaderAdapter>
    concept reader_adapter = requires(ReaderAdapter adapter, byte_t* P, const size_t S) {
        {adapter.read(P, S)};
    };

    template<typename WriterAdapter>
    concept writer_adapter = requires(WriterAdapter adapter, const byte_t* P, const size_t S) {
        {adapter.write(P, S)};
    };
}