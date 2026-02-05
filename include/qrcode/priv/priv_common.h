#ifndef QRCODE_PRIV_COMMON_HEADER
#define QRCODE_PRIV_COMMON_HEADER

#include <stdint.h>

#include <sys/types.h>

#define QRCODE_VERSION_IS_MICRO(ver) ((ver) & (1 << 6))
#define QRCODE_BASE_VERSION(ver) ((ver) & 0b111111)

#define QRCODE_VALID_VERSION(ver) (QRCODE_VERSION_IS_MICRO(ver) ? (((ver) ^ (1 << 6)) >= 1 && ((ver) ^ (1 << 6)) <= 4) : (ver >= 1 && ver <= 40))
#define QRCODE_VALID_ECL(ecl) ((ecl) >= 0 && (ecl) <= 4)

void qrcode_write_bits(uint8_t* buf, ssize_t* bit, uintmax_t val, size_t nbits);


#endif