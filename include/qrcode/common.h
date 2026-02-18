#ifndef QRCODE_COMMON_HEADER
#define QRCODE_COMMON_HEADER

#define QRCODE_MICRO_FLAG         (1 << 6)
#define QRCODE_VERSION_MICRO(ver) ((ver) | QRCODE_MICRO_FLAG)
#define QRCODE_VERSION_BASE(ver)  ((ver) & (QRCODE_MICRO_FLAG - 1))

// 5.1.b
#define QRCODE_ENCODING_NUMERIC      (0)
#define QRCODE_ENCODING_ALPHANUMERIC (1)
#define QRCODE_ENCODING_BYTE         (2)
#define QRCODE_ENCODING_KANJI        (3)
// 5.2
#define QRCODE_MODE_ECI               (4)
#define QRCODE_MODE_STRUCTURED_APPEND (5)
#define QRCODE_MODE_FNC1_1            (6)
#define QRCODE_MODE_FNC1_2            (7)
// Internal
#define QRCODE_TERMINATOR (8)
#define QRCODE_PADDING    (9)

// 5.1.f
#define QRCODE_ECL_L (0)
#define QRCODE_ECL_M (1)
#define QRCODE_ECL_Q (2)
#define QRCODE_ECL_H (3)

#endif