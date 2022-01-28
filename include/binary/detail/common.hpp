#pragma once

#include <concepts> // std::integral, std::floating_point
#include <type_traits> // std::underlying_type_t

namespace thr::binary::detail {
    template<typename T>
    concept arithmetic = std::integral<T> || std::floating_point<T>;

    template<typename T>
    concept numeric = arithmetic<T> || arithmetic<std::underlying_type_t<T>>;
}