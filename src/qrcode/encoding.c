#include "qrcode/encoding.h"

#include "qrcode/info/capacity_info.h"
#include "qrcode/info/encoding_info.h"
#include "qrcode/priv/writing.h"
#include "qrcode/common.h"

#include <stdbool.h>

// 7.4.4
int qrcode_encode_numeric(const uint8_t* data, size_t dlen, uint8_t* buf, int version, int ecl, size_t* out_bit){
    struct qrcode_capacity_info cinfo;
    struct qrcode_encoding_info einfo;
    size_t bits;

    if (qrcode_capacity_info(version, ecl, QRCODE_MODE_NUMERIC, &cinfo) < 0) return -1;
    if (qrcode_encoding_info(version, QRCODE_MODE_NUMERIC, &einfo) < 0) return -1;
    bits = cinfo.codewords*8 - cinfo.truncated*4;

    qrcode_write_bits(buf, einfo.mode, einfo.mode_len, out_bit);
    qrcode_write_bits(buf, dlen, einfo.count_len, out_bit);

    for (size_t a = 0; a < dlen;){
        size_t rem = dlen - a;
        uint16_t val;
        size_t nbits;
        if (rem >= 3){
            val = (data[a] - '0')*100 + (data[a + 1] - '0')*10 + (data[a + 2] - '0');
            nbits = 10;
            a += 3;
        }
        else if (rem == 2){
            val = (data[a] - '0')*10 + (data[a + 1] - '0');
            nbits = 7;
            a += 2;
        }
        else if (rem == 1){
            val = (data[a] - '0');
            nbits = 4;
            a += 1;
        }
        else break;
        if (*out_bit + nbits > bits) return -1;
        qrcode_write_bits(buf, val, nbits, out_bit);
    }

    return 0;
}

// 7.4.10
int qrcode_append_terminator(uint8_t* buf, int version, int ecl, size_t* out_bit){
    struct qrcode_capacity_info cinfo;
    struct qrcode_encoding_info einfo;
    size_t bits;

    if (qrcode_capacity_info(version, ecl, QRCODE_MODE_NUMERIC, &cinfo) < 0) return -1;
    if (qrcode_encoding_info(version, QRCODE_MODE_NUMERIC, &einfo) < 0) return -1;
    bits = cinfo.codewords*8 - cinfo.truncated*4;

    if (*out_bit == bits) return 0;
    if (bits - *out_bit <= einfo.term_len) einfo.term_len = bits - *out_bit;
    if (*out_bit + einfo.term_len > bits) return -1;
    qrcode_write_bits(buf, 0, einfo.term_len, out_bit);

    return 0;
}

// 7.4.11
int qrcode_append_padding(uint8_t* buf, int version, int ecl, size_t* out_bit){
    struct qrcode_capacity_info cinfo;
    struct qrcode_encoding_info einfo;
    size_t bits;

    if (qrcode_capacity_info(version, ecl, QRCODE_MODE_NUMERIC, &cinfo) < 0) return -1;
    if (qrcode_encoding_info(version, QRCODE_MODE_NUMERIC, &einfo) < 0) return -1;
    bits = cinfo.codewords*8 - cinfo.truncated*4;

    bool micro = QRCODE_IS_MICRO(version);
    version = QRCODE_VERSION(version);

    if (*out_bit % 8 != 0 && !(micro && (version == 1 || version == 3))){
        if (*out_bit + (8 - (*out_bit % 8)) > bits) return -1;
        qrcode_write_bits(buf, 0, 8 - (*out_bit % 8), out_bit);
    }
    
    size_t padding = (bits - *out_bit) / 8;
    size_t rem = (bits - *out_bit) % 8;
    for (size_t a = 0; a < padding; a++){
        if (*out_bit + 8 > bits) return -1;
        if (a % 2 == 0) qrcode_write_bits(buf, 0b11101100, 8, out_bit);
        else qrcode_write_bits(buf, 0b00010001, 8, out_bit);
    }
    if (rem && micro && (version == 1 || version == 3)){
        if (*out_bit + 4 > bits) return -1;
        if (padding % 2 == 0) qrcode_write_bits(buf, 0b1110, 4, out_bit);
        else qrcode_write_bits(buf, 0b0001, 4, out_bit);
    }
    return 0;
}