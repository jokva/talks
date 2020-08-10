#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "file.h"

typedef struct file_interface {
    int   (*open)(file*);
    void  (*close)(file*);
    char* (*readline)(file*);
    int   (*iseof)(const file*);
} interface;

/* MAIN */

void cat(interface* fn, file* f) {
    int ok = fn->open(f);
    if (!ok) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    char* ln = NULL;
    while (ln = fn->readline(f))
        printf(ln);

    fn->close(f);
}

int main(int argc, char** argv) {
    cfile cf;
    cfile_init(&cf, argv[1]);

    // Then later methods.open = &noisycfile_open;
    interface methods;
    methods.open = &cfile_open;
    methods.close = &cfile_close;
    methods.readline = &cfile_readline;
    methods.iseof = &cfile_iseof;
    cat(&methods, (file*)&cf);
}
