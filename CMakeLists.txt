cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

# Binary
add_library(LibBinary INTERFACE)

target_include_directories(LibBinary INTERFACE include)

# Binary usage examples

# Streams
project(BinaryStreamsExample)

add_executable(
        BinaryStreamsExample
        src/examples/streams.cpp
)

target_compile_options(BinaryStreamsExample PUBLIC -Wall -Wextra -pedantic -Werror)

target_link_libraries(BinaryStreamsExample LibBinary)

# Iterators
project(BinaryIteratorsExample)

add_executable(
        BinaryIteratorsExample
        src/examples/streams.cpp
)

target_compile_options(BinaryIteratorsExample PUBLIC -Wall -Wextra -pedantic -Werror)

target_link_libraries(BinaryIteratorsExample LibBinary)