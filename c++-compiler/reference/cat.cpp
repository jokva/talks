#include <cstdlib>
#include <cstdio>
#include "file.hpp"

void cat(file* f) {
    auto ok = f->open();
    if (!ok) {
        std::perror("Unable to open file");
        std::exit(EXIT_FAILURE);
    }

    while (auto* r = f->readline())
        std::printf(r);

    if (auto* cf = dynamic_cast< cfile* >(f)) {
        cf->only_c();
    }

    if (auto* cf = dynamic_cast< cppfile* >(f)) {
        cf->only_cpp();
    }

    f->close();
}

int main(int argc, char** argv) {
    cfile cf(argv[1]);
    cppfile cppf(argv[1]);

    cat(&cf);
    std::puts("\n---\n");
    cat(&cppf);
}
