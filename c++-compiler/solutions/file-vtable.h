#ifndef FILE_VTABLE_H
#define FILE_VTABLE_H

struct file;

typedef struct interface {
    int   (*open)(struct file*);
    void  (*close)(struct file*);
    char* (*readline)(struct file*);
    int   (*iseof)(const struct file*);
} interface;

typedef struct file {
    const interface* vtable;
    const char* fpath;
} file;

typedef struct cfile {
    file parent;
    FILE* fp;
} cfile;

/* non-virtuals */
int file_init(file*, const char* p);
const char* file_path(const file*);

/* public interface */
int   file_open(file*);
void  file_close(file*);
char* file_readline(file*);
int   file_iseof(const file*);

int   cfile_init(cfile* self, const char* path);
int   cfile_open(file*);
void  cfile_close(file*);
char* cfile_readline(file*);
int   cfile_iseof(const file*);

#endif //FILE_VTABLE_H
