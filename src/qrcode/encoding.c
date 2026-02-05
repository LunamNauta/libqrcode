#include "qrcode/encoding.h"

#include "qrcode/info/capacity_info.h"
#include "qrcode/info/encoding_info.h"
#include "qrcode/priv/priv_common.h"
#include "qrcode/common.h"

#include <stdint.h>

#include <sys/types.h>

// 7.4.4, pg. 31
// Assumes valid utf8 string
ssize_t qrcode_encode_numeric(const uint8_t* data, uint8_t* buf, size_t dlen, ssize_t bit, int version, int ecl){
    uint16_t val;
    ssize_t cci_len;
    ssize_t mode_ind_len;
    ssize_t mode_ind;
    ssize_t nbits;
    size_t rem;
    ssize_t bits;
    bool truncated;

    for (size_t a = 0; a < dlen; a++){
        if (data[a] < '0' || data[a] > '9') return -1;
    }

    bits = qrcode_capacity_codewords(version, ecl);
    if (bits < 0) return -1;
    truncated = qrcode_capacity_truncated(version);
    bits = bits*8 - truncated*4;

    cci_len = qrcode_encoding_cci_len(version, QRCODE_MODE_NUMERIC);
    mode_ind_len = qrcode_encoding_mi_len(version, QRCODE_MODE_NUMERIC);
    mode_ind = qrcode_encoding_mi(version, QRCODE_MODE_NUMERIC);

    qrcode_write_bits(buf, &bit, mode_ind, mode_ind_len);
    qrcode_write_bits(buf, &bit, dlen, cci_len);

    for (size_t a = 0; a < dlen;){
        rem = dlen - a;
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
        if (bit + nbits > bits) return -1;
        qrcode_write_bits(buf, &bit, val, nbits);
    }
    return bit;
}

// 7.4.10, pg. 37
ssize_t qrcode_add_terminator(uint8_t* buf, ssize_t bit, int version, int ecl){
    ssize_t term_len;
    ssize_t bits;
    bool truncated;

    bits = qrcode_capacity_codewords(version, ecl);
    if (bits < 0) return -1;
    truncated = qrcode_capacity_truncated(version);
    bits = bits*8 - truncated*4;
    term_len = qrcode_encoding_term_len(version, QRCODE_MODE_NUMERIC);

    if (bit == bits) return bit;
    if (bits - bit <= term_len) term_len = bits - bit;
    if (bit + term_len > bits) return -1;
    qrcode_write_bits(buf, &bit, 0, term_len);
    return bit;
}

// 7.4.11, pg. 37
ssize_t qrcode_add_padding(uint8_t* buf, ssize_t bit, int version, int ecl){
    ssize_t bits;
    bool truncated;
    bool micro;

    bits = qrcode_capacity_codewords(version, ecl);
    if (bits < 0) return -1;
    truncated = qrcode_capacity_truncated(version);
    bits = bits*8 - truncated*4;

    micro = QRCODE_VERSION_IS_MICRO(version);
    version = QRCODE_BASE_VERSION(version);

    if (bit % 8 != 0 && !(micro && (version == 1 || version == 3))){
        if (bit + (8 - (bit % 8)) > bits) return -1;
        qrcode_write_bits(buf, &bit, 0, 8 - (bit % 8));
    }
    if (bits < 0) return -1;
    size_t padding = (bits - bit) / 8;
    size_t rem = (bits - bit) % 8;
    for (size_t a = 0; a < padding; a++){
        if (bit + 8 > bits) return -1;
        if (a % 2 == 0) qrcode_write_bits(buf, &bit, 0b11101100, 8);
        else qrcode_write_bits(buf, &bit, 0b00010001, 8);
    }
    if (rem && micro && (version == 1 || version == 3)){
        if (bit + 4 > bits) return -1;
        if (padding % 2 == 0) qrcode_write_bits(buf, &bit, 0b1110, 4);
        else qrcode_write_bits(buf, &bit, 0b0001, 4);
    }
    return bit;
}