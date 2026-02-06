#include "../../../include/qrcode/priv/writing.h"

void qrcode_write_bits(uint8_t* buf, uintmax_t val, size_t nbits, size_t* out_bit){
    uintmax_t val_tmp;
    size_t offset;
    size_t byte;

    for (size_t a = 0; a < nbits; a++){
        val_tmp = (val >> (nbits - 1 - a)) & 0x1;
        byte = (*out_bit) >> 3;
        offset = 7 - ((*out_bit) & 0x7);
        buf[byte] |= val_tmp << offset;
        (*out_bit)++;
    }
}