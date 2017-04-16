#ifndef BINARYIO_H
#define BINARYIO_H

//! \file
//! Functions that help reading and writing BrainVoyager's binary file formats.

//#include "glm/glm.hpp"
#include <cstdint>
#include <istream>
#include <ostream>
#include <vector>

//! Read a char
char read_char(std::istream& stream);

//! Read an 8-bit unsigned integer.
std::uint8_t read_uint8(std::istream& stream);

//! Read a 16-bit unsigned integer.
std::uint16_t read_uint16(std::istream& stream);

//! Read a 32-bit unsigned integer
std::uint32_t read_uint32(std::istream& stream);

//! Read three-element vector stored as 16-bit unsigned integers.
//glm::ivec3 read_ivec3_as_uint16_triple(std::istream& stream);

//! Read single-precision float.
float read_float(std::istream& stream);

//! Reads string (marco's version)
std::string read_string(std::istream& stream);

//! Read a zero-terminated string.
std::string read_zstring(std::istream& stream);

//! Read the remainder of the input.
std::vector<char> read_everything(std::istream& stream);

//! Write an 8-bit unsigned integer.
void write_uint8(std::ostream& stream, uint8_t u);

//! Write a 16-bit unsigned integer.
void write_uint16(std::ostream& stream, uint16_t u);

//! Write a 32-bit unsigned integer.
void write_uint16(std::ostream& stream, uint32_t u);

//! Write a three-element vector as 16-bit unsigned integers.
//void write_ivec3_as_uint16_triple(std::ostream& stream, const glm::ivec3& v);

//! Write a single-precision float.
void write_float(std::ostream& stream, float f);

//! Write as a zero-terminated string.
void write_zstring(std::ostream& stream, const std::string& s);

#endif // BINARYIO_H
