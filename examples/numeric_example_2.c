#include "helper.h"

#include "qrcode/encoding.h"
#include "qrcode/common.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

// Example 2 from 7.4.4, pg. 31

int main(){
    const char* input = "0123456789012345";
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
}

// 00 10000 0000001100 0101011001 1010100110 1110000101 0011101010 0101 0000000

// Mode Indicator      : 00
// Character Count     : 10000
// Data                : 0000001100 0101011001 1010100110 1110000101 0011101010 0101
// Terminator          : 0000000
// Boundary Padding    : N/A (Bit capacity reached)
// Alternating Padding : N/A (Bit capacity reached)