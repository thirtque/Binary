#pragma once

#include <cstdint> // std::*int*_t
#include <string> // std::string

#include <binary/binary.hpp> // thr::binary::Writer, thr::binary::Reader

struct Header {
        std::uint32_t signature;
        std::uint8_t entryCount;
};

struct Entry {
        std::string name;
        std::uint32_t value;
};

template<typename OutputAdapter>
void writeHeader(thr::binary::Writer<OutputAdapter>& writer, const Header& header) {
    writer.write(header.signature);
    writer.write(header.entryCount);
}

template<typename InputAdapter>
Header readHeader(thr::binary::Reader<InputAdapter>& reader) {
    Header fileHeader;
    reader.read(fileHeader.signature);
    reader.read(fileHeader.entryCount);
    return fileHeader;
}

template<typename OutputAdapter>
void writeEntry(thr::binary::Writer<OutputAdapter>& writer, const Entry& entry) {
    writer.write(entry.name, 16);
    writer.write(entry.value);
}

template<typename InputAdapter>
Entry readEntry(thr::binary::Reader<InputAdapter>& reader) {
    Entry fileEntry;
    reader.read(fileEntry.name, 16);
    reader.read(fileEntry.value);
    return fileEntry;
}
