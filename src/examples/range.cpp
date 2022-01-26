#include <iostream> // std::cout, std::endl
#include <vector> // std::vector

#include <binary/binary.hpp> // thr::binary::writer, thr::binary::reader

#include "examples/common.hpp"

void write(std::vector<std::byte>& outputBuffer) {
    auto writer = thr::binary::writer(std::back_inserter(outputBuffer));

    writeHeader(writer,
        {
            0x746872,
            3,
        });

    writeEntry(writer, {"Entry1", 623});
    writeEntry(writer, {"Entry2", 423});
    writeEntry(writer, {"Entry3", 512});
}

void read(std::vector<std::byte>& inputBuffer) {
    auto reader = thr::binary::reader(inputBuffer);

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
}

int main() {
    std::vector<std::byte> buffer;

    write(buffer);
    read(buffer);
}