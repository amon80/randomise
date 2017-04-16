#ifndef IOERROR_H
#define IOERROR_H

//! Exception classes used by file reading/writing code.

#include <stdexcept>

//! Thrown to report an error with file input/output.
class IOError : public std::runtime_error {
public:
    explicit IOError(const std::string& w) : std::runtime_error(w) { }
    explicit IOError(const char * w) : std::runtime_error(w) { }
};

//! Thrown to report an error with opening a file.
class OpenFileError : public IOError {
public:
    explicit OpenFileError(const std::string& w) : IOError(w) { }
    explicit OpenFileError(const char * w) : IOError(w) { }
};

//! Thrown to report an error with reading a file.
class ReadFileError : public IOError {
public:
    explicit ReadFileError(const std::string& w) : IOError(w) { }
    explicit ReadFileError(const char * w) : IOError(w) { }
};

//! Thrown to report an error with writing a file.
class WriteFileError : public IOError {
public:
    explicit WriteFileError(const std::string& w) : IOError(w) { }
    explicit WriteFileError(const char * w) : IOError(w) { }
};

#endif //IOERROR_H
