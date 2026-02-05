#ifndef EXAMPLES_HELPER_HEADER
#define EXAMPLES_HELPER_HEADER

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static void dump_hex(const uint8_t* buf, size_t bits){
    size_t bytes = (bits + 7) / 8;
    for (size_t a = 0; a < bytes; a++){
        printf("%02X ", buf[a]);
    }
    printf("\n");
}

static void dump_bits(const uint8_t* buf, size_t bits){
    for (size_t a = 0; a < bits; a++){
        size_t byte = a >> 3;
        size_t off  = 7 - (a & 7);
        printf("%d", (buf[byte] >> off) & 1);
        if ((a & 3) == 3) printf(" ");
    }
    printf("\n");
}

#endif