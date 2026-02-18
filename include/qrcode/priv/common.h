#ifndef QRCODE_PRIV_COMMON_HEADER
#define QRCODE_PRIV_COMMON_HEADER

#include <stddef.h>
#include <stdint.h>

void qrcode_write_bits(uint8_t* buf, uintmax_t val, size_t nbits, size_t* ref_bit);

#endif