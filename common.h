#ifndef QRCODE_COMMON_HEADER
#define QRCODE_COMMON_HEADER

#include <stdint.h>

#include <sys/types.h>

#define QRCODE_VERSION_NORMAL (0)
#define QRCODE_VERSION_MICRO  (1 << 6)
//-------------------------------------------------
#define QRCODE_VERSION(ver) ((ver) & 0b111111)
#define QRCODE_MICRO(ver) (ver | QRCODE_VERSION_MICRO)
#define QRCODE_VERSION_IS_MICRO(ver) (((ver) & QRCODE_VERSION_MICRO) == QRCODE_VERSION_MICRO)
#define QRCODE_VERSION_VALID(ver) ((ver) < (QRCODE_VERSION_MICRO << 1) && ((QRCODE_VERSION_IS_MICRO(ver) && (QRCODE_VERSION(ver) >= 1 && QRCODE_VERSION(ver) <= 4)) || ((ver) >= 1 && (ver) <= 40)))

#define QRCODE_MODE_ECI               (1)      // 7.3.2, pg. 26
#define QRCODE_MODE_NUMERIC           (2)      // 7.3.3, pg. 27
#define QRCODE_MODE_ALPHANUMERIC      (3)      // 7.3.4, pg. 27
#define QRCODE_MODE_BYTE              (4)      // 7.3.5, pg. 27
#define QRCODE_MODE_KANJI             (5)      // 7.3.6, pg. 27
#define QRCODE_MODE_STRUCTURED_APPEND (6)      // 7.3.8, pg. 28
#define QRCODE_MODE_FNC1              (7)      // 7.4.1, pg. 28
#define QRCODE_MODE_ALT               (1 << 4) // For FNC1 position 1 and position 2
//-------------------------------------------------
#define QRCODE_MODE(mode) ((mode) & 0b111)
#define QRCODE_MODE_IS_ALT(mode) (((mode) & QRCODE_MODE_ALT) == QRCODE_MODE_ALT)
#define QRCODE_MODE_VALID(mode) ((mode) <= QRCODE_MODE_ALT && ((QRCODE_MODE_IS_ALT(mode) && (QRCODE_MODE(mode) == QRCODE_MODE_FNC1)) || ((mode) >= QRCODE_MODE_ECI && (mode) <= QRCODE_MODE_FNC1)))
#define QRCODE_MODE_VALID_BASE(mode) ((mode) == QRCODE_MODE_NUMERIC || (mode) == QRCODE_MODE_ALPHANUMERIC || (mode) == QRCODE_MODE_BYTE || (mode) == QRCODE_MODE_KANJI)

#define QRCODE_ECL_L    (0)
#define QRCODE_ECL_M    (1)
#define QRCODE_ECL_Q    (2)
#define QRCODE_ECL_H    (3)
#define QRCODE_ECL_NONE (4)
//-------------------------------------------------
#define QRCODE_ECL_VALID(ecl) (((ecl) >= QRCODE_ECL_L && (ecl) <= QRCODE_ECL_H) || ((ecl) == QRCODE_ECL_NONE))

static void qrcode_write_bits(uint8_t* buf, ssize_t* bit, uintmax_t val, size_t nbits){
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

// 7.4.5, table 5, pg. 32
static int qrcode_alpha_to(uint8_t from){
    if (from >= '0' && from <= '9') return from - '0';
    if (from >= 'A' && from <= 'Z') return from - 'A' + 10;
    switch (from){
        case ' ': return 36;
        case '$': return 37;
        case '%': return 38;
        case '*': return 39;
        case '+': return 40;
        case '-': return 41;
        case '.': return 42;
        case '/': return 43;
        case ':': return 44;
    }
    return -1;
}

#endif