#ifndef QRCODE_PRIV_WRITING_HEADER
#define QRCODE_PRIV_WRITING_HEADER

#include <stddef.h>
#include <stdint.h>

void qrcode_write_bits(uint8_t* buf, uintmax_t val, size_t nbits, size_t* out_bit);

#endif