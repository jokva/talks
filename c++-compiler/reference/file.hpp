#ifndef FILE_HPP
#define FILE_HPP

#include <cstdlib>
#include <fstream>

class file {
public:
    explicit file(const char* p) : fpath(p) {}

    /* non-virtuals */
    const char* path() const {
        return this->fpath;
    }

    /* non-const virtuals */
    virtual int open() = 0;
    virtual void close() = 0;
    virtual char* readline() = 0;

    /* const virtuals */
    virtual int iseof() const = 0;

private:
    const char* fpath;
};

class cfile : public file {
public:
    using file::file;

    int open() override;
    void close() override;
    char* readline() override;

    int iseof() const override;

    void only_c() const;

private:
    std::FILE* fp;
};

class noisycfile : public cfile {
public:
    using cfile::cfile;

    int open() override;
    void close() override;
};

class cppfile : public file {
public:
    using file::file;

    int open() override;
    void close() override;
    char* readline() override;

    int iseof() const override;

    void only_cpp() const;

private:
    std::fstream fs;
};

#endif //FILE_HPP
