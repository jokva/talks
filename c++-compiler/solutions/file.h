#ifndef FILE_H
#define FILE_H

typedef struct {
    const char* fpath;
} file;

/* non-virtuals */
int file_init(file*, const char* p);
const char* file_path(const file*);

/* virtuals */
int   file_open(file*);
void  file_close(file*);
char* file_readline(file*);
int   file_iseof(const file*);

typedef struct {
    file parent;
    FILE* fp;
} cfile;

int   cfile_init(cfile*, const char* path);
int   cfile_open(file*);
void  cfile_close(file*);
char* cfile_readline(file*);
int   cfile_iseof(const file*);

#endif //FILE_H
