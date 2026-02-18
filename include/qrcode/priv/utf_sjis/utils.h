#ifndef QRCODE_PRIV_UTF_SJIS_UTILS_HEADER
#define QRCODE_PRIV_UTF_SJIS_UTILS_HEADER

#include "qrcode/priv/utf_sjis/sjis_tbl.h"
#include "qrcode/priv/utf_sjis/utf_tbl.h"

#include <stdint.h>

uint32_t qrcode_sjiscp2utfcp(uint16_t sjis);
uint16_t qrcode_utfcp2sjiscp(uint32_t utf);

#endif