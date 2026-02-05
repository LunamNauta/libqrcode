#include "qrcode/info/encoding_info.h"

#include "qrcode/priv/priv_common.h"
#include "qrcode/common.h"

#include <stdint.h>

// 7.4.2, table 2, pg. 29
// 7.4.2, table 3, pg. 29
__attribute__((pure)) int32_t qrcode_encoding_info(int version, int mode){
    if (!QRCODE_VALID_VERSION(version) || mode > QRCODE_MODE_KANJI) return -1;

    bool micro = QRCODE_VERSION_IS_MICRO(version);
    version = QRCODE_BASE_VERSION(version);
    int32_t cci_len;

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
    switch (mode){
        case QRCODE_MODE_NUMERIC:      cci_len = version <= 9 ? 10 : (version <= 26  ? 12 : (version <= 40 ? 14 : -1)); break;
        case QRCODE_MODE_ALPHANUMERIC: cci_len = version <= 9 ? 9  : (version <= 26  ? 11 : (version <= 40 ? 13 : -1)); break;
        case QRCODE_MODE_BYTE:         cci_len = version <= 9 ? 8  : (version <= 26  ? 16 : (version <= 40 ? 16 : -1)); break;
        case QRCODE_MODE_KANJI:        cci_len = version <= 9 ? 8  : (version <= 26  ? 10 : (version <= 40 ? 12 : -1)); break;
        default: return -1;
    }
    cci_len <<= 11;
    switch (mode){
        case QRCODE_MODE_ECI:               return cci_len | 0b10001000111;
        case QRCODE_MODE_NUMERIC:           return cci_len | 0b10001000001;
        case QRCODE_MODE_ALPHANUMERIC:      return cci_len | 0b10001000010;
        case QRCODE_MODE_BYTE:              return cci_len | 0b10001000100;
        case QRCODE_MODE_KANJI:             return cci_len | 0b10001001000;
        case QRCODE_MODE_STRUCTURED_APPEND: return cci_len | 0b10001000011;
        case QRCODE_MODE_FNC1_1:            return cci_len | 0b10001000101;
        case QRCODE_MODE_FNC1_2:            return cci_len | 0b10001001001;
        default: return -1;
    }
}