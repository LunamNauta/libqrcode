#include "helper.h"

#include "qrcode/encoding.h"
#include "qrcode/common.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

// Example 1 from 7.4.4, pg. 31

int main(){
    const char* input = "01234567";
    uint8_t buf[64] = {0};
    ssize_t bit = 0;
    int version = 1;
    int ecl = QRCODE_ECL_H;
    
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

// 0001 0000001000 0000001100 0101011001 1000011 0000 000 11101100 00010001 11101100

// Mode Indicator      : 0001
// Character Count     : 0000001000
// Data                : 0000001100 0101011001 1000011
// Terminator          : 0000
// Boundary Padding    : 000
// Alternating Padding : 11101100 00010001 11101100