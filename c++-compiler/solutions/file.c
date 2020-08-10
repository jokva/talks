#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

int file_init(file* self, const char* path) {
    self->fpath = strcpy(malloc(strlen(path) + 1), path);
    return true;
}

const char* file_path(const file* self) {
    return self->fpath;
}

int cfile_init(cfile* self, const char* path) {
    return file_init((file*)self, path);
}

int cfile_open(file* pself) {
    cfile* self = (cfile*)pself;
    self->fp = fopen(pself->fpath, "r");
    return (bool)self->fp;
}

void cfile_close(file* pself) {
    cfile* self = (cfile*)pself;
    if (self->fp)
        fclose(self->fp);
    self->fp = NULL;
}

char* cfile_readline(file* pself) {
    cfile* self = (cfile*)pself;
    char* line = NULL;
    int size = 2;

    while (true) {
        const int c = fgetc(self->fp);

        if (c == EOF) {
            return line;
        }

        line = realloc(line, size);
        line[size - 2] = c;
        line[size - 1] = '\0';
        size += 1;
        if (c == '\n') {
            return line;
        }
    }
}

int cfile_iseof(const file* pself) {
    return feof(((const cfile*)pself)->fp);
}

int noisycfile_open(file* self) {
    printf("Opening %s\n", file_path(self));
    return cfile_open(self);
}

void noisycfile_close(file* self) {
    printf("Closing %s\n", file_path(self));
    return cfile_close(self);
}
