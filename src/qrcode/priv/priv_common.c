#include "qrcode/priv/priv_common.h"

#include <stdint.h>

#include <sys/types.h>

void qrcode_write_bits(uint8_t* buf, ssize_t* bit, uintmax_t val, size_t nbits){
    uintmax_t val_tmp;
    size_t offset;
    size_t byte;

    for (size_t a = 0; a < nbits; a++){
        val_tmp = (val >> (nbits - 1 - a)) & 0x1;
        byte = (*bit) >> 3;
        offset = 7 - ((*bit) & 0x7);
        buf[byte] |= val_tmp << offset;
        (*bit)++;
    }
}