#include "qrcode/encoding.h"

#include "qrcode/info/capacity_info.h"
#include "qrcode/info/encoding_info.h"
#include "qrcode/priv/common.h"
#include "qrcode/validation.h"
#include "qrcode/common.h"

int qrcode_encode_numeric(uint8_t* buf, const uint8_t* data, size_t dlen, int ver, int ecl, size_t* ref_bit){
    struct qrcode_capacity_info cinfo;
    struct qrcode_encoding_info einfo;
    size_t bits;

    if (qrcode_capacity_info(ver, ecl, QRCODE_ENCODING_NUMERIC, &cinfo) < 0) return -1;
    if (qrcode_encoding_info(ver, QRCODE_ENCODING_NUMERIC, &einfo) < 0) return -1;
    bits = cinfo.codewords*8 - cinfo.truncated*4;

    qrcode_write_bits(buf, einfo.mode, einfo.mode_len, ref_bit);
    qrcode_write_bits(buf, dlen, einfo.count_len, ref_bit);

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
        if (*ref_bit + nbits > bits) return -1;
        qrcode_write_bits(buf, val, nbits, ref_bit);
    }

    return 0;
}
int qrcode_encode_alphanumeric(uint8_t* buf, const uint8_t* data, size_t dlen, int ver, int ecl, size_t* ref_bit);
int qrcode_encode_byte(uint8_t* buf, const uint8_t* data, size_t dlen, int ver, int ecl, size_t* ref_bit);
int qrcode_encode_kanji(uint8_t* buf, const uint8_t* data, size_t dlen, int ver, int ecl, size_t* ref_bit);

int qrcode_append_terminator(uint8_t* buf, int ver, int ecl, size_t* ref_bit){
    struct qrcode_capacity_info cinfo;
    struct qrcode_encoding_info einfo;
    size_t bits;

    if (qrcode_capacity_info(ver, ecl, QRCODE_ENCODING_NUMERIC, &cinfo) < 0) return -1;
    if (qrcode_encoding_info(ver, QRCODE_ENCODING_NUMERIC, &einfo) < 0) return -1;
    bits = cinfo.codewords*8 - cinfo.truncated*4;

    if (*ref_bit == bits) return 0;
    if (bits - *ref_bit <= einfo.term_len) einfo.term_len = bits - *ref_bit;
    if (*ref_bit + einfo.term_len > bits) return -1;
    qrcode_write_bits(buf, 0, einfo.term_len, ref_bit);

    return 0;
}
int qrcode_append_padding(uint8_t* buf, int ver, int ecl, size_t* ref_bit){
    struct qrcode_capacity_info cinfo;
    struct qrcode_encoding_info einfo;
    size_t bits;

    if (qrcode_capacity_info(ver, ecl, QRCODE_ENCODING_NUMERIC, &cinfo) < 0) return -1;
    if (qrcode_encoding_info(ver, QRCODE_ENCODING_NUMERIC, &einfo) < 0) return -1;
    bits = cinfo.codewords*8 - cinfo.truncated*4;

    bool micro = QRCODE_IS_MICRO(ver);
    ver = QRCODE_VERSION_BASE(ver);

    if (*ref_bit % 8 != 0 && !(micro && (ver == 1 || ver == 3))){
        if (*ref_bit + (8 - (*ref_bit % 8)) > bits) return -1;
        qrcode_write_bits(buf, 0, 8 - (*ref_bit % 8), ref_bit);
    }
    
    size_t padding = (bits - *ref_bit) / 8;
    size_t rem = (bits - *ref_bit) % 8;
    for (size_t a = 0; a < padding; a++){
        if (*ref_bit + 8 > bits) return -1;
        if (a % 2 == 0) qrcode_write_bits(buf, 0b11101100, 8, ref_bit);
        else qrcode_write_bits(buf, 0b00010001, 8, ref_bit);
    }
    if (rem && micro && (ver == 1 || ver == 3)){
        if (*ref_bit + 4 > bits) return -1;
        if (padding % 2 == 0) qrcode_write_bits(buf, 0b1110, 4, ref_bit);
        else qrcode_write_bits(buf, 0b0001, 4, ref_bit);
    }
    return 0;
}