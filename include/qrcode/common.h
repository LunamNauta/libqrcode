#ifndef QRCODE_COMMON_HEADER
#define QRCODE_COMMON_HEADER

#include <errno.h>

#define QRCODE_MICRO_FLAG (1 << 6)
#define QRCODE_IS_MICRO(ver) ((ver) & QRCODE_MICRO_FLAG)
#define QRCODE_MICRO(ver) ((ver) | QRCODE_MICRO_FLAG)
#define QRCODE_VERSION(ver) ((ver) & 0b111111)

// 5.1.b
#define QRCODE_MODE_NUMERIC      (0) // 7.3.3
#define QRCODE_MODE_ALPHANUMERIC (1) // 7.3.4
#define QRCODE_MODE_BYTE         (2) // 7.3.5
#define QRCODE_MODE_KANJI        (3) // 7.3.6

// 5.2
#define QRCODE_MODE_STRUCTURED_APPEND (4) // 8
#define QRCODE_MODE_ECI               (5) // 7.4.3.2

// 5.1.f
#define QRCODE_ECL_L (0)
#define QRCODE_ECL_M (1)
#define QRCODE_ECL_Q (2)
#define QRCODE_ECL_H (3)

#define QRCODE_ERROR(err, ret) (errno = (err), ret)
#define QRCODE_INVALID_VERSION  (1)
#define QRCODE_INVALID_ENCODING (2)
#define QRCODE_INVALID_ECL      (4)
#define QRCODE_INVALID_COMBO    (8)
#define QRCODE_INVALID_DATA     (16)
#define QRCODE_INVALID_BUF_LEN  (32)

#endif