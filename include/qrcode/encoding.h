#ifndef QRCODE_ENCODING_HEADER
#define QRCODE_ENCODING_HEADER

#include <stddef.h>
#include <stdint.h>

// Other than ECI modes, 'data' is assumed to be a valid UTF-8 encoded string
// If 'data' is not a valid UTF-8 string, undefined behavior is invoked

// In ECI modes, 'data' is assumed to be a valid 'eci' encoded string
// If 'data' is not a valid 'eci' encoded string, undefined behavior is invoked

// 7.4.4
int qrcode_encode_numeric(const uint8_t* data, size_t dlen, uint8_t* buf, int version, int ecl, size_t* out_bit);

// 7.4.5
int qrcode_encode_alphanumeric(const uint8_t* data, size_t dlen, uint8_t* buf, int version, int ecl, size_t* out_bit);

// 7.4.6
int qrcode_encode_byte(const uint8_t* data, size_t dlen, uint8_t* buf, int version, int ecl, size_t* out_bit);

// 7.4.7
int qrcode_encode_kanji(const uint8_t* data, size_t dlen, uint8_t* buf, int version, int ecl, size_t* out_bit);

// 7.4.3.2
int qrcode_encode_eci(const uint8_t* data, size_t dlen, uint8_t* buf, int version, int ecl, int eci, size_t* out_bit);

// 8
int qrcode_append_structured(uint8_t* buf, int version, int ecl, int position, int total, int parity, size_t* out_bit);

// 7.4.10
int qrcode_append_terminator(uint8_t* buf, int version, int ecl, size_t* out_bit);

// 7.4.11
int qrcode_append_padding(uint8_t* buf, int version, int ecl, size_t* out_bit);

#endif