#ifndef QRCODE_ENCODING_INFO_HEADER
#define QRCODE_ENCODING_INFO_HEADER

#include "common.h"

#include <stdbool.h>
#include <stdint.h>

// 7.4.2, table 2, pg. 29
// 7.4.2, table 3, pg. 29
#define QRCODE_CCI_LENGTH(info)             (((info) & 0b1111100000000000) >> 11)
#define QRCODE_MODE_INDICATOR_LENGTH(info)  (((info) & 0b0000011100000000) >> 8)
#define QRCODE_TERMINATOR_LENGTH(info)      (((info) & 0b0000000011110000) >> 4)
#define QRCODE_MODE_INDICATOR_VALUE(info)   ((info) & ((1 << QRCODE_MODE_INDICATOR_LENGTH(info)) - 1))
#define QRCODE_ENCODING_INFO_INVALID(info)  ((info) == ((uint16_t)(-1)))
static uint16_t qrcode_encoding_info(int version, int mode){
    bool micro = QRCODE_VERSION_IS_MICRO(version);
    version = QRCODE_VERSION(version);
    bool alt = QRCODE_MODE_IS_ALT(mode);
    mode = QRCODE_MODE(mode);

    if (micro) switch (version){
        case 1: switch (mode){
            case QRCODE_MODE_NUMERIC: return 0b0001100000110000;
            default: return -1;
        }
        case 2: switch (mode){
            case QRCODE_MODE_NUMERIC:      return 0b0001000101010000;
            case QRCODE_MODE_ALPHANUMERIC: return 0b0001100101010001;
            default: return -1;
        }
        case 3: switch (mode){
            case QRCODE_MODE_NUMERIC:      return 0b0010101001110000;
            case QRCODE_MODE_ALPHANUMERIC: return 0b0010001001110001;
            case QRCODE_MODE_BYTE:         return 0b0010001001110010;
            case QRCODE_MODE_KANJI:        return 0b0001101001110011;
            default: return -1;
        }
        case 4: switch (mode){
            case QRCODE_MODE_NUMERIC:      return 0b0011001110010000;
            case QRCODE_MODE_ALPHANUMERIC: return 0b0010101110010001;
            case QRCODE_MODE_BYTE:         return 0b0010101110010010;
            case QRCODE_MODE_KANJI:        return 0b0010001110010011;
            default: return -1;
        }
        default: return -1;
    }
    int16_t cci_len;
    switch (mode){
        case QRCODE_MODE_NUMERIC:      cci_len = version <= 9 ? 10 : (version <= 26  ? 12 : (version <= 40 ? 14 : -1));
        case QRCODE_MODE_ALPHANUMERIC: cci_len = version <= 9 ? 9  : (version <= 26  ? 11 : (version <= 40 ? 13 : -1));
        case QRCODE_MODE_BYTE:         cci_len = version <= 9 ? 8  : (version <= 26  ? 16 : (version <= 40 ? 16 : -1));
        case QRCODE_MODE_KANJI:        cci_len = version <= 9 ? 8  : (version <= 26  ? 10 : (version <= 40 ? 12 : -1));
        default: return -1;
    }
    if (cci_len < 0) return -1;
    cci_len <<= 11;
    switch (mode){
        case QRCODE_MODE_ECI:               return cci_len | 0b10001000111;
        case QRCODE_MODE_NUMERIC:           return cci_len | 0b10001000001;
        case QRCODE_MODE_ALPHANUMERIC:      return cci_len | 0b10001000010;
        case QRCODE_MODE_BYTE:              return cci_len | 0b10001000100;
        case QRCODE_MODE_KANJI:             return cci_len | 0b10001001000;
        case QRCODE_MODE_STRUCTURED_APPEND: return cci_len | 0b10001000011;
        case QRCODE_MODE_FNC1:              return cci_len | (alt ? 0b10001001001 : 0b10001000101);
        default: return -1;
    }
}

#endif