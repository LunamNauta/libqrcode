#ifndef QRCODE_ENCODING_HEADER
#define QRCODE_ENCODING_HEADER

#include "capacity_info.h"
#include "encoding_info.h"
#include "common.h"

#include <stdint.h>

#include <sys/types.h>

// 7.4.4, pg. 31
#define QRCODE_NUMERIC_LENGTH(version, dlen) (QRCODE_MODE_LENGTH(qrcode_mode_info(version, QRCODE_MODE_NUMERIC)) + qrcode_cci_length(version, QRCODE_MODE_NUMERIC) + 10*(dlen / 3) + ((4*(dlen % 3)) & 0b0111))
// Assumes valid utf8 string
static ssize_t qrcode_encode_numeric(const uint8_t* data, uint8_t* buf, size_t dlen, ssize_t bit, int version, int ecl){
    uint16_t val;
    ssize_t enc_info;
    ssize_t cci_len;
    ssize_t mode_ind_len;
    ssize_t mode_ind;
    size_t nbits;
    size_t rem;
    ssize_t bits;

    bits = QRCODE_DATA_BITS(version, ecl);
    if (QRCODE_CAPACITY_INFO_INVALID(bits)) return -1;
    enc_info = qrcode_encoding_info(version, QRCODE_MODE_NUMERIC);
    if (QRCODE_ENCODING_INFO_INVALID(enc_info)) return -1;

    cci_len = QRCODE_CCI_LENGTH(enc_info);
    mode_ind_len = QRCODE_MODE_INDICATOR_LENGTH(enc_info);
    mode_ind = QRCODE_MODE_INDICATOR_VALUE(enc_info);

    qrcode_write_bits(buf, &bit, mode_ind, mode_ind_len);
    qrcode_write_bits(buf, &bit, dlen, cci_len);

    for (size_t a = 0; a < dlen;){
        rem = dlen - a;
        if (rem >= 3){
            int8_t v1 = data[a];
            if (v1 < '0' || v1 > '9') return -1;
            int8_t v2 = data[a + 1];
            if (v2 < '0' || v2 > '9') return -1;
            int8_t v3 = data[a + 2];
            if (v3 < '0' || v3 > '9') return -1;
            val = (v1 - '0')*100 + (v2 - '0')*10 + (v3 - '0');
            nbits = 10;
            a += 3;
        }
        else if (rem == 2){
            int8_t v1 = data[a];
            if (v1 < '0' || v1 > '9') return -1;
            int8_t v2 = data[a + 1];
            if (v2 < '0' || v2 > '9') return -1;
            val = (v1 - '0')*10 + (v2 - '0');
            nbits = 7;
            a += 2;
        }
        else if (rem == 1){
            int8_t v1 = data[a];
            if (v1 < '0' || v1 > '9') return -1;
            val = (v1 - '0');
            nbits = 4;
            a += 1;
        }
        if (bit + nbits > bits) return -1;
        qrcode_write_bits(buf, &bit, val, nbits);
    }
    return bit;
}

// 7.4.5, pg. 32
#define QRCODE_ALPHANUMERIC_LENGTH(version, dlen) (QRCODE_MODE_LENGTH(qrcode_mode_info(version, QRCODE_MODE_ALPHANUMERIC)) + qrcode_cci_length(version, QRCODE_MODE_ALPHANUMERIC) + 11*(dlen / 2) + 6*(dlen % 2))
// Assumes valid utf8 string
static ssize_t qrcode_encode_alphanumeric(const uint8_t* data, uint8_t* buf, size_t dlen, ssize_t bit, int version, int ecl){    
    uint16_t val;
    ssize_t enc_info;
    ssize_t cci_len;
    ssize_t mode_ind_len;
    ssize_t mode_ind;
    size_t nbits;
    size_t rem;
    ssize_t bits;

    if (QRCODE_VERSION_IS_MICRO(version) && QRCODE_VERSION(version) == 1) return -1;
    bits = QRCODE_DATA_BITS(version, ecl);
    if (QRCODE_CAPACITY_INFO_INVALID(bits)) return -1;
    enc_info = qrcode_encoding_info(version, QRCODE_MODE_NUMERIC);
    if (QRCODE_MODE_INDICATOR_LENGTH(enc_info)) return -1;

    cci_len = QRCODE_CCI_LENGTH(enc_info);
    mode_ind_len = QRCODE_MODE_INDICATOR_LENGTH(enc_info);
    mode_ind = QRCODE_MODE_INDICATOR_VALUE(enc_info);

    qrcode_write_bits(buf, &bit, mode_ind, mode_ind_len);
    qrcode_write_bits(buf, &bit, dlen, cci_len);

    for (size_t a = 0; a < dlen;){
        rem = dlen - a;
        if (rem >= 2){
            int v1 = qrcode_alpha_to(data[a]);
            if (v1 < 0) return -1;
            int v2 = qrcode_alpha_to(data[a + 1]);
            if (v2 < 0) return -1;
            val = v1*45 + v2;
            nbits = 11;
            a += 2;
        }
        else{
            int v1 = qrcode_alpha_to(data[a]);
            if (v1 < 0) return -1;
            val = v1;
            nbits = 6;
            a += 1;
        }
        if (bit + nbits > bits) return -1;
        qrcode_write_bits(buf, &bit, val, nbits);
    }
    return bit;
}

// 7.4.10, pg. 37
static ssize_t qrcode_add_terminator(uint8_t* buf, ssize_t bit, int version, int ecl){
    ssize_t bits = QRCODE_DATA_BITS(version, ecl);
    if (bits < 0) return -1;

    ssize_t enc_info;
    ssize_t term_len;

    enc_info = qrcode_encoding_info(version, QRCODE_MODE_NUMERIC);
    if (QRCODE_ENCODING_INFO_INVALID(enc_info)) return -1;
    term_len = QRCODE_TERMINATOR_LENGTH(enc_info);

    if (bit == bits) return bit;
    if (bits - bit <= term_len) term_len = bits - bit;
    if (bit + term_len > bits) return -1;
    qrcode_write_bits(buf, &bit, 0, term_len);
    return bit;
}

// 7.4.11, pg. 37
static ssize_t qrcode_add_padding(uint8_t* buf, ssize_t bit, int version, int ecl){
    ssize_t bits = QRCODE_DATA_BITS(version, ecl);
    if (bits < 0) return -1;

    if (bit % 8 != 0 && !(QRCODE_VERSION_IS_MICRO(version) && (QRCODE_VERSION(version) == 1 || QRCODE_VERSION(version) == 3))){
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
    if (rem && QRCODE_VERSION_IS_MICRO(version) && (QRCODE_VERSION(version) == 1 || QRCODE_VERSION(version) == 3)){
        if (bit + 4 > bits) return -1;
        if (padding % 2 == 0) qrcode_write_bits(buf, &bit, 0b1110, 4);
        else qrcode_write_bits(buf, &bit, 0b0001, 4);
    }
    return bit;
}

#endif