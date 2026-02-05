#ifndef QRCODE_CAPACITY_INFO_HEADER
#define QRCODE_CAPACITY_INFO_HEADER

#include "qrcode/priv/priv_common.h"

#include <stdint.h>

__attribute__((pure)) int64_t qrcode_capacity_info(int version, int ecl);

__attribute__((always_inline)) inline int8_t qrcode_capacity_truncated(int version){
    if (!QRCODE_VALID_VERSION(version)) return -1;
    bool micro = QRCODE_VERSION_IS_MICRO(version);
    version = QRCODE_BASE_VERSION(version);
    return micro && (version == 1 || version == 3);
}
__attribute__((always_inline)) inline int16_t qrcode_capacity_codewords(int version, int ecl){
    int64_t info = qrcode_capacity_info(version, ecl);
    if (info < 0) return -1;
    return ((info >> 48) & 0b111111111111);
}
__attribute__((always_inline)) inline int16_t qrcode_capacity_mode(int version, int ecl, int mode){
    int64_t info = qrcode_capacity_info(version, ecl);
    if (info < 0) return -1;
    int64_t tmp = ((info >> mode*12) & 0b111111111111);
    if (tmp == 0) return -1;
    return tmp;
}

#endif