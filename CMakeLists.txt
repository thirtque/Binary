cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

option(LIBBINARY_EXAMPLES "Compile examples" ON)

# Binary
add_library(LibBinary INTERFACE)

target_include_directories(LibBinary INTERFACE include)

# Binary usage examples
if (LIBBINARY_EXAMPLES)
    # Stream
    project(BinaryStreamExample)

    add_executable(
            BinaryStreamExample
            src/examples/stream.cpp
    )

    target_compile_options(BinaryStreamExample PUBLIC -Wall -Wextra -pedantic -Werror)

    target_link_libraries(BinaryStreamExample LibBinary)

    # Iterator
    project(BinaryIteratorExample)

    add_executable(
            BinaryIteratorExample
            src/examples/iterator.cpp
    )

    target_compile_options(BinaryIteratorExample PUBLIC -Wall -Wextra -pedantic -Werror)

    target_link_libraries(BinaryIteratorExample LibBinary)

    # Range
    project(BinaryRangeExample)

    add_executable(
            BinaryRangeExample
            src/examples/range.cpp
    )

    target_compile_options(BinaryRangeExample PUBLIC -Wall -Wextra -pedantic -Werror)

    target_link_libraries(BinaryRangeExample LibBinary)
endif ()