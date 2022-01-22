#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <binary/binary.hpp>

using namespace std::string_literals;

int main() {
    {
        auto outputFile = std::ofstream("data.bin", std::ofstream::binary | std::ofstream::out | std::ofstream::trunc);

        auto writer = thr::binary::Writer(outputFile);

        writer.write(std::byte{42});
        writer.write<std::uint32_t>(1);
        writer.write("abcdef"s);

        outputFile.close();
    }
    {
        auto inputFile = std::ifstream("data.bin", std::ifstream::binary | std::ifstream::in);

        auto reader = thr::binary::Reader(inputFile);

        std::byte a;
        reader.read(a);
        std::cout << std::to_integer<std::uint32_t>(a) << std::endl;

        std::uint32_t b;
        reader.read(b);
        std::cout << b << std::endl;

        std::string c;
        reader.read(c, 6);
        std::cout << c << std::endl;

        inputFile.close();
    }

    return 0;
}
