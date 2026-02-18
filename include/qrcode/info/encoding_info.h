#ifndef QRCODE_INFO_ENCODING_INFO_HEADER
#define QRCODE_INFO_ENCODING_INFO_HEADER

#include <stdint.h>

struct qrcode_encoding_info{
    uint8_t mode : 4;
    uint8_t mode_len : 3;
    uint8_t term_len : 4;
    uint8_t count_len : 5;
};

// 7.4.2, table 2/3
int qrcode_encoding_info(int ver, int mode, struct qrcode_encoding_info* out_info);

#endif