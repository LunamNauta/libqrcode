#ifndef QRCODE_ERROR_HEADER
#define QRCODE_ERROR_HEADER

#include <errno.h>

#define QRCODE_ERROR_COMBO         (1)
#define QRCODE_ERROR_VERSION       (2)
#define QRCODE_ERROR_ENCODING      (4)
#define QRCODE_ERROR_MODE          (8)
#define QRCODE_ERROR_ENCODING_MODE (QRCODE_ERROR_ENCODING | QRCODE_ERROR_MODE)
#define QRCODE_ERROR_ECL           (16)
#define QRCODE_ERROR_DATA          (32)

#define QRCODE_ERROR(err, ret) (errno = (err), ret)

#endif