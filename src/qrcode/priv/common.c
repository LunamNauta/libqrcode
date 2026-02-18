#include "qrcode/priv/common.h"

void qrcode_write_bits(uint8_t* buf, uintmax_t val, size_t nbits, size_t* ref_bit){
    uintmax_t val_tmp;
    size_t offset;
    size_t byte;

    for (size_t a = 0; a < nbits; a++){
        val_tmp = (val >> (nbits - a - 1)) & 0x1;
        byte = (*ref_bit) >> 3;
        offset = 7 - ((*ref_bit) & 0x07);
        buf[byte] |= val_tmp << offset;
        (*ref_bit)++;
    }
}