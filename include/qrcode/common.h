#ifndef QRCODE_COMMON_HEADER
#define QRCODE_COMMON_HEADER

#define QRCODE_MICRO(ver)   ((ver) | (1 << 6))

#define QRCODE_MODE_NUMERIC           (0)
#define QRCODE_MODE_ALPHANUMERIC      (1)
#define QRCODE_MODE_BYTE              (2)
#define QRCODE_MODE_KANJI             (3)
#define QRCODE_MODE_FNC1_1            (4)
#define QRCODE_MODE_FNC1_2            (5)
#define QRCODE_MODE_ECI               (6)
#define QRCODE_MODE_STRUCTURED_APPEND (7 << 5)

#define QRCODE_ECL_M1 (0)
#define QRCODE_ECL_L  (1)
#define QRCODE_ECL_M  (2)
#define QRCODE_ECL_Q  (3)
#define QRCODE_ECL_H  (4)

#endif