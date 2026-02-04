#include "common.h"

#include <string.h>
#include <stdio.h>

static void dump_hex(const uint8_t* buf, size_t bits){
    size_t bytes = (bits + 7) / 8;
    for (size_t i = 0; i < bytes; i++){
        printf("%02X ", buf[i]);
    }
    printf("\n");
}

static void dump_bits(const uint8_t* buf, size_t bits){
    for (size_t i = 0; i < bits; i++){
        size_t byte = i >> 3;
        size_t off  = 7 - (i & 7);
        printf("%d", (buf[byte] >> off) & 1);
        if ((i & 3) == 3) printf(" ");
    }
    printf("\n");
}

int main(void){
    const char *input = "012345678901234567";
    uint8_t buf[64] = {0};
    ssize_t bit = 0;
    int version = QRCODE_MICRO(3);
    int ecl = QRCODE_ECL_M;
    
    bit = qrcode_encode_numeric((const uint8_t*)input, buf, strlen(input), bit, version, ecl);
    if (bit < 0){printf("Encoding failed\n"); return -1;}
    bit = qrcode_add_terminator(buf, bit, version, ecl);
    if (bit < 0){printf("Encoding failed\n"); return -1;}
    bit = qrcode_add_padding(buf, bit, version, ecl);
    if (bit < 0){printf("Encoding failed\n"); return -1;}

    printf("Input: \"%s\"\n", input);
    printf("Bits written: %zd\n", bit);

    printf("Hex output:\n");
    dump_hex(buf, bit);

    printf("Bit output:\n");
    dump_bits(buf, bit);

    return 0;
}