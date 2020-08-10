#include <array>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>

#include "file.hpp"

char* copystr(const char* src, int size) {
    auto* s = (char*)std::malloc(size + 1);
    std::memcpy(s, src, size);
    s[size] = '\0';
    return s;
}

int cfile::open() {
    this->fp = std::fopen(this->path(), "r");
    return bool(this->fp);
}

void cfile::close() {
    if (this->fp)
        std::fclose(this->fp);
    this->fp = nullptr;
}

char* cfile::readline() {
    std::vector< char > buffer;

    while (true) {
        const auto c = fgetc(this->fp);
        if (c == EOF) {
            return nullptr;
        }

        buffer.push_back(c);
        if (c == '\n') {
            return copystr(buffer.data(), buffer.size());
        }
    }
}

int cfile::iseof() const {
    return std::feof(this->fp);
}

void cfile::only_c() const {
    std::puts("c!");
}

int noisycfile::open() {
    std::printf("Opening %s\n", this->path());
    return this->cfile::open();
}

void noisycfile::close() {
    std::printf("Closing %s\n", this->path());
    return this->cfile::close();
}

int cppfile::open() {
    this->fs.open(this->path());
    return this->fs.is_open();
}

void cppfile::close() {
    this->fs.close();
}

char* cppfile::readline() {
    std::string line;
    std::getline(this->fs, line);
    if (line.empty())
        return nullptr;

    line += "\n";
    return copystr(line.data(), line.size());
}

int cppfile::iseof() const {
    return this->fs.eof();
}

void cppfile::only_cpp() const {
    std::puts("c++!");
}
