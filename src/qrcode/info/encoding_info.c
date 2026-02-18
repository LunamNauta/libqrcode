#include "qrcode/info/encoding_info.h"

#include "qrcode/validation.h"
#include "qrcode/common.h"
#include "qrcode/error.h"

#include <stdbool.h>

int qrcode_encoding_info(int ver, int mode, struct qrcode_encoding_info* out_info){
    bool micro = QRCODE_IS_MICRO(ver);
    ver = QRCODE_VERSION_BASE(ver);

    if (micro) switch (ver){
        case 1: switch (mode){
            case QRCODE_ENCODING_NUMERIC: *out_info = (struct qrcode_encoding_info){0, 0, 3, 3}; return 0;
            return QRCODE_ERROR(QRCODE_ERROR_COMBO | QRCODE_ERROR_VERSION | QRCODE_ERROR_ENCODING, -1);
        } break;
        case 2: switch (mode){
            case QRCODE_ENCODING_NUMERIC:      *out_info = (struct qrcode_encoding_info){0b0, 1, 5, 4}; return 0;
            case QRCODE_ENCODING_ALPHANUMERIC: *out_info = (struct qrcode_encoding_info){0b1, 1, 5, 3}; return 0;
            return QRCODE_ERROR(QRCODE_ERROR_COMBO | QRCODE_ERROR_VERSION | QRCODE_ERROR_ENCODING, -1);
        } break;
        case 3: switch (mode){
            case QRCODE_ENCODING_NUMERIC:      *out_info = (struct qrcode_encoding_info){0b00, 2, 7, 5}; return 0;
            case QRCODE_ENCODING_ALPHANUMERIC: *out_info = (struct qrcode_encoding_info){0b01, 2, 7, 4}; return 0;
            case QRCODE_ENCODING_BYTE:         *out_info = (struct qrcode_encoding_info){0b10, 2, 7, 4}; return 0;
            case QRCODE_ENCODING_KANJI:        *out_info = (struct qrcode_encoding_info){0b11, 2, 7, 3}; return 0;
            return QRCODE_ERROR(QRCODE_ERROR_COMBO | QRCODE_ERROR_VERSION | QRCODE_ERROR_ENCODING, -1);
        } break;
        case 4: switch (mode){
            case QRCODE_ENCODING_NUMERIC:      *out_info = (struct qrcode_encoding_info){0b000, 3, 9, 6}; return 0;
            case QRCODE_ENCODING_ALPHANUMERIC: *out_info = (struct qrcode_encoding_info){0b001, 3, 9, 5}; return 0;
            case QRCODE_ENCODING_BYTE:         *out_info = (struct qrcode_encoding_info){0b010, 3, 9, 5}; return 0;
            case QRCODE_ENCODING_KANJI:        *out_info = (struct qrcode_encoding_info){0b011, 3, 9, 4}; return 0;
            return QRCODE_ERROR(QRCODE_ERROR_COMBO | QRCODE_ERROR_VERSION | QRCODE_ERROR_ENCODING, -1);
        } break;
        return QRCODE_ERROR(QRCODE_ERROR_VERSION, -1);
    }
    switch (mode){
        case QRCODE_ENCODING_NUMERIC:       *out_info = (struct qrcode_encoding_info){0b0001, 4, 4, (uint8_t)(ver <= 9 ? 10 : (ver <= 26  ? 12 : 14))}; return 0;
        case QRCODE_ENCODING_ALPHANUMERIC:  *out_info = (struct qrcode_encoding_info){0b0010, 4, 4, (uint8_t)(ver <= 9 ? 9  : (ver <= 26  ? 11 : 13))}; return 0;
        case QRCODE_ENCODING_BYTE:          *out_info = (struct qrcode_encoding_info){0b0100, 4, 4, (uint8_t)(ver <= 9 ? 8  : (ver <= 26  ? 16 : 16))}; return 0;
        case QRCODE_ENCODING_KANJI:         *out_info = (struct qrcode_encoding_info){0b1000, 4, 4, (uint8_t)(ver <= 9 ? 8  : (ver <= 26  ? 10 : 12))}; return 0;
        case QRCODE_MODE_STRUCTURED_APPEND: *out_info = (struct qrcode_encoding_info){0b0011, 4, 4, 0}; return 0;
        case QRCODE_MODE_ECI:               *out_info = (struct qrcode_encoding_info){0b0111, 4, 4, 0}; return 0;
        return QRCODE_ERROR(QRCODE_ERROR_COMBO | QRCODE_ERROR_VERSION | QRCODE_ERROR_ENCODING, -1);
    }

    return 0;
}