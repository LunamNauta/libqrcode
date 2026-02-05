#ifndef QRCODE_ENCODING_HEADER
#define QRCODE_ENCODING_HEADER

#include <stdint.h>

#include <sys/types.h>

// Assumes valid utf8 string
ssize_t qrcode_encode_numeric(const uint8_t* data, uint8_t* buf, size_t dlen, ssize_t bit, int version, int ecl);

ssize_t qrcode_add_terminator(uint8_t* buf, ssize_t bit, int version, int ecl);

ssize_t qrcode_add_padding(uint8_t* buf, ssize_t bit, int version, int ecl);

#endif