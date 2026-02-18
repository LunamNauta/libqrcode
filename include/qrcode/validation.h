#ifndef QRCODE_VALIDATION_HEADER
#define QRCODE_VALIDATION_HEADER

#include "qrcode/common.h"

#define QRCODE_IS_MICRO(ver)      ((ver) & QRCODE_MICRO_FLAG)
#define QRCODE_VALID_VERSION(ver) ((ver < (QRCODE_MICRO_FLAG << 1)) && QRCODE_VERSION_BASE(ver) >= 1 && (QRCODE_IS_MICRO(ver) ? QRCODE_VERSION_BASE(ver) <= 4 : QRCODE_VERSION_BASE(ver) <= 40))

#define QRCODE_VALID_ENCODING(enc)           ((enc) >= QRCODE_ENCODING_NUMERIC && (enc) <= QRCODE_ENCODING_KANJI)
#define QRCODE_VALID_MODE(mode)              ((mode) >= QRCODE_MODE_ECI && (mode) <= QRCODE_MODE_FNC1_2)
#define QRCODE_VALID_ENCODING_MODE(enc_mode) ((enc_mode) >= QRCODE_ENCODING_NUMERIC && (enc_mode) <= QRCODE_MODE_FNC1_2)
#define QRCODE_VALID_ECL(ecl)                ((ecl) >= QRCODE_ECL_L && (ecl) <= QRCODE_ECL_H)

#endif