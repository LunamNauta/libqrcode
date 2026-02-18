#ifndef QRCODE_INFO_CAPACITY_INFO_HEADER
#define QRCODE_INFO_CAPACITY_INFO_HEADER

#include <stdint.h>

struct qrcode_capacity_info{
    uint64_t codewords : 12;
    uint64_t numeric : 13;
    uint64_t alphanumeric : 13;
    uint64_t byte : 12;
    uint64_t kanji : 11;
    uint64_t truncated : 1;
};

// 7.4.11, table 7
int qrcode_capacity_info(int ver, int ecl, int mode, struct qrcode_capacity_info* out_info);

#endif