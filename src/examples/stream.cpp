#include <fstream> // std::ofstream, std::istream
#include <iostream> // std::cout, std::endl

#include <binary/binary.hpp> // thr::binary::writer, thr::binary::reader

#include "examples/common.hpp"

constexpr auto fileName = "binary_file.bin";

void write() {
    std::ofstream outputStream(fileName, std::ofstream::in | std::ofstream::binary | std::ofstream::trunc);

    auto writer = thr::binary::writer{thr::binary::output_adapter(outputStream)};

    writeHeader(writer,
        {
            0x746872,
            3,
        });

    writeEntry(writer, {"Entry1", 623});
    writeEntry(writer, {"Entry2", 423});
    writeEntry(writer, {"Entry3", 512});

    outputStream.close();
}

void read() {
    std::ifstream inputStream(fileName, std::ifstream::in | std::ifstream::binary);

    auto reader = thr::binary::reader{thr::binary::input_adapter(inputStream)};

    auto header = readHeader(reader);
    std::cout << "header.signature = 0x" << std::hex << header.signature << std::dec << std::endl;
    std::cout << "header.entryCount = " << static_cast<std::uint32_t>(header.entryCount) << std::endl;
    std::cout << std::endl;

    for (auto i = 0; i < header.entryCount; i++) {
        auto entry = readEntry(reader);
        std::cout << "entry.name = " << entry.name << std::endl;
        std::cout << "entry.value = " << entry.value << std::endl;
        std::cout << std::endl;
    }

    inputStream.close();
}

int main() {
    write();
    read();
}
