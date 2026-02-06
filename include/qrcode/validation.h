#ifndef QRCODE_VALIDATION_HEADER
#define QRCODE_VALIDATION_HEADER

#include "common.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

bool qrcode_valid_numeric(const uint8_t* data, size_t dlen);
bool qrcode_valid_alphanumeric(const uint8_t* data, size_t dlen);
bool qrcode_valid_byte(const uint8_t* data, size_t dlen);
bool qrcode_valid_kanji(const uint8_t* data, size_t dlen);

#define QRCODE_VALID_VERSION(ver)\
(QRCODE_IS_MICRO(ver) \
    ? (((ver) ^ QRCODE_MICRO_FLAG) >= 1 && ((ver) ^ QRCODE_MICRO_FLAG) <= 4) \
    : ((ver) >= 1 && (ver) <= 40) \
)

#define QRCODE_VALID_ENCODING(mode)\
((mode) >= QRCODE_MODE_NUMERIC && (mode) <= QRCODE_MODE_KANJI)

#define QRCODE_VALID_ECL(ecl)\
((ecl) >= QRCODE_ECL_L && (ecl) <= QRCODE_ECL_H)

#endif