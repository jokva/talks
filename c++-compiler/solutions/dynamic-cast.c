#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "file-vtable.h"

typedef struct noisycfile {
    file parent;
    FILE* fp;
} noisycfile;

void only_cfile(const cfile* cf) {
    puts("Only cfile! Meow!");
}

void only_noisy(const noisycfile* cf) {
    puts("Only noisy! Rawr!");
}

int file_init(file* self, const char* path) {
    self->fpath = strcpy(malloc(strlen(path) + 1), path);
    return true;
}

int file_open(file* self) {
    return self->vtable->open(self);
}

void file_close(file* self) {
    self->vtable->close(self);
}

char* file_readline(file* self) {
    return self->vtable->readline(self);
}

int file_iseof(const file* self) {
    return self->vtable->iseof(self);
}

/* copy from file.c */

const char* file_path(const file* self) {
    return self->fpath;
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

char* noisycfile_readline(file* pself) {
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

int noisycfile_iseof(const file* pself) {
    return feof(((const cfile*)pself)->fp);
}

/* PUNCHLINE */

static const interface cfile_vtable = {
    .open       = &cfile_open,
    .close      = &cfile_close,
    .readline   = &cfile_readline,
    .iseof      = &cfile_iseof,
};

static const interface noisycfile_vtable = {
    .open       = &noisycfile_open,
    .close      = &noisycfile_close,
    /* these are defaulted and "inherited" from cfile */
    .readline   = &noisycfile_readline,
    .iseof      = &noisycfile_iseof,
};

#define DYNAMIC_CAST(type, ptr) \
    *(uintptr_t**) &(*f) == (uintptr_t*) &(type ## _vtable) \
    ? (type*)ptr : NULL

int cfile_init(cfile* self, const char* path) {
    int err = file_init((file*)self, path);
    self->parent.vtable = &cfile_vtable;
    return err;
}

int noisycfile_init(cfile* self, const char* path) {
    int err = cfile_init(self, path);
    self->parent.vtable = &noisycfile_vtable;
    return err;
}

void cat(file* f) {
    int ok = file_open(f);
    if (!ok) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    char* ln = NULL;
    while (ln = file_readline(f))
        printf(ln);

    cfile* cf = DYNAMIC_CAST(cfile, f);
    if (cf) {
        only_cfile(cf);
    }

    // noisycfile* noisy = f->vtable == &noisycfile_vtable ? (noisycfile*)f : NULL;
    noisycfile* noisy = DYNAMIC_CAST(noisycfile, f);
    if (noisy) {
        only_noisy(noisy);
    }

    file_close(f);
}

int main(int argc, char** argv) {
    cfile quiet;
    cfile_init(&quiet, argv[1]);

    cfile noisy;
    noisycfile_init(&noisy, argv[1]);

    cat((file*)&quiet);
    puts("\n----\n");
    cat((file*)&noisy);
}

