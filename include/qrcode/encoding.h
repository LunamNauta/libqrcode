#ifndef QRCODE_ENCODING_HEADER
#define QRCODE_ENCODING_HEADER

#include <stddef.h>
#include <stdint.h>

// 7.4.4
int qrcode_encode_numeric(uint8_t* buf, const uint8_t* data, size_t dlen, int ver, int ecl, size_t* ref_bit);
// 7.4.5
int qrcode_encode_alphanumeric(uint8_t* buf, const uint8_t* data, size_t dlen, int ver, int ecl, size_t* ref_bit);
// 7.4.6
int qrcode_encode_byte(uint8_t* buf, const uint8_t* data, size_t dlen, int ver, int ecl, size_t* ref_bit);
// 7.4.7
int qrcode_encode_kanji(uint8_t* buf, const uint8_t* data, size_t dlen, int ver, int ecl, size_t* ref_bit);

// 7.4.10
int qrcode_append_terminator(uint8_t* buf, int ver, int ecl, size_t* ref_bit);
// 7.4.11
int qrcode_append_padding(uint8_t* buf, int ver, int ecl, size_t* ref_bit);

#endif