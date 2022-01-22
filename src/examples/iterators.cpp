#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <binary/binary.hpp>

using namespace std::string_literals;

int main() {
    std::vector<std::byte> buffer;

    {
        auto outputIterator = std::back_inserter(buffer);

        auto writer = thr::binary::Writer(outputIterator);

        writer.write(std::byte{42});
        writer.write<std::uint32_t>(1);
        writer.write("abcdef"s);
    }
    {
        auto inputIterator = buffer.begin();
        auto inputSentinel = buffer.end();

        auto reader = thr::binary::Reader(inputIterator, inputSentinel);

        std::byte a;
        reader.read(a);
        std::cout << std::to_integer<std::uint32_t>(a) << std::endl;

        std::uint32_t b;
        reader.read(b);
        std::cout << b << std::endl;

        std::string c;
        reader.read(c, 6);
        std::cout << c << std::endl;
    }

    return 0;
}
