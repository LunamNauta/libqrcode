#ifndef QRCODE_ENCODING_INFO_HEADER
#define QRCODE_ENCODING_INFO_HEADER

#include <stdint.h>

__attribute__((pure)) int32_t qrcode_encoding_info(int version, int mode);

__attribute__((always_inline)) static inline int8_t qrcode_encoding_term_len(int version, int mode){
    int32_t info = qrcode_encoding_info(version, mode);
    if (info < 0) return -1;
    return ((info >> 4) & 0b1111);
}
__attribute__((always_inline)) static inline int8_t qrcode_encoding_cci_len(int version, int mode){
    int32_t info = qrcode_encoding_info(version, mode);
    if (info < 0) return -1;
    return ((info >> 11) & 0b11111);
}
__attribute__((always_inline)) static inline int8_t qrcode_encoding_mi_len(int version, int mode){
    int32_t info = qrcode_encoding_info(version, mode);
    if (info < 0) return -1;
    return ((info >> 8) & 0b111);
}
__attribute__((always_inline)) static inline int8_t qrcode_encoding_mi(int version, int mode){
    int32_t info = qrcode_encoding_info(version, mode);
    if (info < 0) return -1;
    return (info & 0b1111);
}

#endif