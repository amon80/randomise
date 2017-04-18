#include "binaryio.h"
#include <sstream>
#include "ioerror.h"

char read_char(std::istream& stream){
    char c;
    stream.read(reinterpret_cast<char * >(&c), sizeof(c));
    if (stream.fail())
        throw ReadFileError("error reading from binary file");
    return c;
}

std::uint8_t read_uint8(std::istream& stream) {
    std::uint8_t u(0);
    stream.read(reinterpret_cast<char * >(&u), sizeof(u));
    if (stream.fail())
        throw ReadFileError("error reading from binary file");
    return u;
}

std::uint16_t read_uint16(std::istream& stream) {
    std::uint16_t u(0);
    stream.read(reinterpret_cast<char * >(&u), sizeof(u));
    if (stream.fail())
        throw ReadFileError("error reading from binary file");
    return u;
}

std::uint32_t read_uint32(std::istream& stream) {
    std::uint32_t u(0);
    stream.read(reinterpret_cast<char * >(&u), sizeof(u));
    if (stream.fail())
        throw ReadFileError("error reading from binary file");
    return u;
}

/*
glm::ivec3 read_ivec3_as_uint16_triple(std::istream& stream) {
    glm::ivec3 vec;
    vec.x = read_uint16(stream);
    vec.y = read_uint16(stream);
    vec.z = read_uint16(stream);
    return vec;
}
*/

float read_float(std::istream& stream) {
    float f(0.0f);
    stream.read(reinterpret_cast<char * >(&f), sizeof(f));
    if (stream.fail())
        throw ReadFileError("error reading from binary file");
    return f;
}

std::string read_string(std::istream& stream){
    std::string toReturn;
    while(true){
        char c = read_char(stream);
        if(iscntrl(c)){
            break;
        }
        toReturn += c;
    }
    return toReturn;
}

//NOTE: Seems to be not working, use the method above instead
std::string read_zstring(std::istream& stream) {
    std::stringbuf buffer;
    stream.get(buffer, '\0');
    stream.get(); // consume the '\0'
    if (stream.fail())
        throw ReadFileError("error reading from binary file");
    return buffer.str();
}

std::vector<char> read_everything(std::istream& stream) {
    const unsigned block_size = 1024;
    unsigned read_total = 0;
    std::vector<char> v(block_size);
    while (true) {
        stream.read(&v[read_total], block_size);
        unsigned read = stream.gcount();
        read_total += read;
        if (stream.eof()) {
            v.resize(read_total);
            return v;
        } else if (stream.fail()) {
            throw ReadFileError("error reading from binary file");
        } else {
            v.resize(read_total + block_size);
        }
    }
}

void write_uint32(std::ostream& stream, uint32_t u) {
    stream.write(reinterpret_cast<char * >(&u), sizeof(u));
    if (stream.fail())
        throw WriteFileError("error writing to binary file");
}

void write_uint16(std::ostream& stream, uint16_t u) {
    stream.write(reinterpret_cast<char * >(&u), sizeof(u));
    if (stream.fail())
        throw WriteFileError("error writing to binary file");
}

void write_uint8(std::ostream& stream, uint8_t u) {
    stream.write(reinterpret_cast<char * >(&u), sizeof(u));
    if (stream.fail())
        throw WriteFileError("error writing to binary file");
}

/*
void write_ivec3_as_uint16_triple(std::ostream& stream, const glm::ivec3& v) {
    write_uint16(stream, v.x);
    write_uint16(stream, v.y);
    write_uint16(stream, v.z);
}
*/

void write_float(std::ostream& stream, float f) {
    stream.write(reinterpret_cast<char * >(&f), sizeof(f));
    if (stream.fail())
        throw WriteFileError("error writing to binary file");
}

void write_zstring(std::ostream& stream, const std::string& s) {
    stream.write(s.c_str(), s.size() + 1);
    if (stream.fail())
        throw WriteFileError("error writing to binary file");
}
