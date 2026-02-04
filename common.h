#ifndef QRCODE_COMMON_HEADER
#define QRCODE_COMMON_HEADER

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <sys/types.h>

#define QRCODE_VERSION_NORMAL (0)
#define QRCODE_VERSION_MICRO  (1 << 6)
#define QRCODE_VERSION_IS_MICRO(ver) (((ver) & QRCODE_VERSION_MICRO) == QRCODE_VERSION_MICRO)
#define QRCODE_VERSION(ver) ((ver) & 0b111111)
#define QRCODE_VERSION_VALID(ver) ((ver) < (QRCODE_VERSION_MICRO << 1) && ((QRCODE_VERSION_IS_MICRO(ver) && (QRCODE_VERSION(ver) >= 1 && QRCODE_VERSION(ver) <= 4)) || ((ver) >= 1 && (ver) <= 40)))
#define QRCODE_MICRO(ver) (ver | QRCODE_VERSION_MICRO)

#define QRCODE_MODE_ECI               (1) // 7.3.2, pg. 26
#define QRCODE_MODE_NUMERIC           (2) // 7.3.3, pg. 27
#define QRCODE_MODE_ALPHANUMERIC      (3) // 7.3.4, pg. 27
#define QRCODE_MODE_BYTE              (4) // 7.3.5, pg. 27
#define QRCODE_MODE_KANJI             (5) // 7.3.6, pg. 27
#define QRCODE_MODE_STRUCTURED_APPEND (6) // 7.3.8, pg. 28
#define QRCODE_MODE_FNC1              (7) // 7.4.1, pg. 28
#define QRCODE_MODE_ALT               (1 << 4)
#define QRCODE_MODE_IS_ALT(mode) (((mode) & QRCODE_MODE_ALT) == QRCODE_MODE_ALT)
#define QRCODE_MODE(mode) ((mode) & 0b111)
#define QRCODE_MODE_VALID(mode) ((mode) <= QRCODE_MODE_ALT && ((QRCODE_MODE_IS_ALT(mode) && (QRCODE_MODE(mode) == QRCODE_MODE_FNC1)) || ((mode) >= QRCODE_MODE_ECI && (mode) <= QRCODE_MODE_FNC1)))
#define QRCODE_MODE_VALID_BASE(mode) ((mode) == QRCODE_MODE_NUMERIC || (mode) == QRCODE_MODE_ALPHANUMERIC || (mode) == QRCODE_MODE_BYTE || (mode) == QRCODE_MODE_KANJI)

#define QRCODE_ECL_L    (0)
#define QRCODE_ECL_M    (1)
#define QRCODE_ECL_Q    (2)
#define QRCODE_ECL_H    (3)
#define QRCODE_ECL_NONE (4)
#define QRCODE_ECL_VALID(ecl) (((ecl) >= QRCODE_ECL_L && (ecl) <= QRCODE_ECL_H) || ((ecl) == QRCODE_ECL_NONE))

// 7.4.11, table 7, pg. 38
static int32_t qrcode_data_capacity_table[1056] = {
    3,  20, 5,  -1, -1, -1,
    -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1,

    5,  40, 10, 6,  -1, -1,
    4,  32, 8,  5,  -1, -1,
    -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1,

    11, 84, 23, 14, 9, 6,
    9,  68, 18, 11, 7, 4,
    -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1,

    16, 128, 35, 21, 15, 9,
    14, 112, 30, 18, 13, 8,
    10, 80,  21, 13, 9,  5,
    -1, -1, -1, -1, -1, -1,
    
    19, 152, 41, 25, 17, 10,
    16, 128, 34, 20, 14, 8,
    13, 104, 27, 16, 11, 7,
    9,  72,  17, 10, 7,  4,
    
    34, 272, 77, 47, 32, 20,
    28, 224, 63, 38, 26, 16,
    22, 176, 48, 29, 20, 12,
    16, 128, 34, 20, 14, 8,

    55, 440, 127, 77, 53, 32,
    44, 352, 101, 61, 42, 26,
    34, 272, 77,  47, 32, 20,
    26, 208, 58,  35, 24, 15,

    80, 640, 187, 114, 78, 48,
    64, 512, 149, 90,  62, 38,
    48, 384, 111, 67,  46, 28,
    36, 288, 82,  50,  34, 21,

    108, 864, 255, 154, 106, 65,
    86,  688, 202, 122, 84,  52,
    62,  496, 144, 87,  60,  37,
    46,  368, 106, 64,  44,  27,

    136, 1088, 322, 196, 134, 82,
    108, 864,  255, 154, 106, 65,
    76,  608,  178, 108, 74,  45,
    60,  480,  139, 84,  58,  36,

    156, 1248, 370, 224, 154, 95,
    124, 992,  293, 178, 122, 75,
    88,  704,  207, 125, 86,  53,
    66,  528,  154, 93,  64,  39,

    194, 1552, 461, 279, 192, 118,
    154, 1232, 365, 221, 152, 93,
    110, 880,  259, 157, 108, 66,
    86,  688,  202, 122, 84,  52,

    232, 1856, 552, 335, 230, 141,
    182, 1456, 432, 262, 180, 111,
    132, 1056, 312, 189, 130, 80,
    100, 800,  235, 143, 98,  60,

    274, 2192, 652, 395, 271, 167,
    216, 1728, 513, 311, 213, 131,
    154, 1232, 364, 221, 151, 93,
    122, 976,  288, 174, 119, 74,

    324, 2592, 772, 468, 321, 198,
    254, 2032, 604, 366, 251, 155,
    180, 1440, 427, 259, 177, 109,
    140, 1120, 331, 200, 137, 85,

    370, 2960, 883, 535, 367, 226,
    290, 2320, 691, 419, 287, 177,
    206, 1648, 489, 296, 203, 125,
    158, 1264, 374, 227, 155, 96,

    428, 3424, 1022, 619, 425, 262,
    334, 2672, 796,  483, 331, 204,
    244, 1952, 580,  352, 241, 149,
    180, 1440, 427,  259, 177, 109,

    461, 3688, 1101, 667, 458, 282,
    365, 2920, 871,  528, 362, 223,
    261, 2088, 621,  376, 258, 159,
    197, 1576, 468,  283, 194, 120,

    523, 4184, 1250, 758, 520, 320,
    415, 3320, 991,  600, 412, 254,
    295, 2360, 703,  426, 292, 180,
    223, 1784, 530,  321, 220, 136,

    589, 4712, 1408, 854, 586, 361,
    453, 3624, 1082, 656, 450, 277,
    325, 2600, 755,  470, 322, 198,
    253, 2024, 602,  365, 250, 154,

    647, 5176, 1548, 938, 644, 397,
    507, 4056, 1212, 734, 504, 310,
    367, 2936, 876,  531, 364, 224,
    313, 2264, 674,  408, 280, 173,

    795, 5768, 1725, 1046, 718, 442,
    563, 4504, 1346, 816,  560, 345,
    397, 3176, 948,  574,  394, 243,
    313, 2504, 746,  452,  310, 191,

    795, 6360, 1903, 1153, 792, 488,
    627, 5016, 1500, 909,  624, 384,
    445, 3560, 1063, 644,  442, 272,
    341, 2728, 813,  493,  338, 208,

    861, 6888, 2061, 1249, 858, 528,
    669, 5352, 1600, 970,  666, 410,
    485, 3880, 1159, 702,  482, 297,
    385, 3080, 919,  557,  382, 235,
    
    932, 7456, 2232, 1352, 929, 572,
    714, 5712, 1708, 1035, 711, 438,
    512, 4096, 1224, 742,  509, 314,
    406, 3248, 969,  587,  403, 248,

    1006, 8048, 2409, 1460, 1003, 618,
    782,  6256, 1872, 1134, 779,  480,
    568,  4544, 1358, 823,  565,  348,
    442,  3536, 1056, 640,  439,  270,

    1094, 8752, 2620, 1588, 1091, 672,
    860,  6880, 2059, 1248, 857,  528,
    614,  4912, 1468, 890,  611,  376,
    464,  3712, 1108, 672,  461,  284,

    1174, 9392, 2812, 1704, 1171, 721,
    914,  7312, 2188, 1326, 911,  561,
    664,  5312, 1588, 963,  661,  407,
    514,  4112, 1228, 744,  511,  315,

    1276, 10208, 3057, 1853, 1273, 784,
    1000, 8000,  2395, 1451, 997,  614,
    718,  5744,  1718, 1041, 715,  440,
    538,  4304,  1286, 779,  535,  330,

    1370, 10960, 3283, 1990, 1367, 842,
    1062, 8496,  2544, 1542, 1059, 652,
    754,  6032,  1804, 1094, 751,  462,
    596,  4768,  1425, 864,  593,  365,

    1468, 11744, 3517, 2132, 1465, 902,
    1128, 9024,  2701, 1637, 1125, 692,
    808,  6464,  1933, 1172, 805,  496,
    628,  5024,  1501, 910,  625,  385,

    1531, 12248, 3669, 2223, 1528, 940,
    1193, 9544,  2857, 1732, 1190, 732,
    871,  6968,  2085, 1263, 868,  534,
    661,  5288,  1581, 958,  658,  405,

    1631, 13048, 3909, 2369, 1628, 1002,
    1267, 10136, 3035, 1839, 1264, 778,
    911,  7288,  2181, 1322, 908,  559,
    701,  5608,  1677, 1016, 698,  430,

    1735, 13880, 4158, 2520, 1732, 1066,
    1373, 10984, 3289, 1994, 1370, 843,
    985,  7880,  2358, 1429, 982,  604,
    745,  5960,  1782, 1080, 742,  457,

    1843, 14744, 4417, 2677, 1840, 1132,
    1455, 11640, 3486, 2113, 1452, 894,
    1033, 8264,  2473, 1499, 1030, 634,
    793,  6344,  1897, 1150, 790,  486,

    1955, 15640, 4686, 2840, 1952, 1201,
    1541, 12328, 3693, 2238, 1538, 947,
    1115, 8920,  2670, 1618, 1112, 684,
    845,  6760,  2022, 1226, 842,  518,

    2071, 16568, 4965, 3009, 2068, 1273,
    1631, 13048, 3909, 2369, 1628, 1002,
    1171, 9368,  2805, 1700, 1168, 719,
    901,  7208,  2157, 1307, 898,  553,

    2191, 17528, 5253, 3183, 2188, 1347,
    1725, 13800, 4134, 2506, 1722, 1060,
    1231, 9848,  2949, 1787, 1228, 756,
    961,  7688,  2301, 1394, 958,  590,

    2306, 18448, 5529, 3351, 2303, 1417,
    1812, 14496, 4343, 2632, 1809, 1113,
    1286, 10288, 2081, 1867, 1283, 790,
    986,  7888,  2361, 1431, 983,  605,

    2434, 19472, 5836, 3537, 2431, 1496,
    1914, 15312, 4588, 2780, 1911, 1176,
    1354, 10832, 3244, 1966, 1351, 832,
    1054, 8432,  2524, 1530, 1051, 647,

    2566, 20528, 6153, 3729, 2563, 1577,
    1992, 15936, 4775, 2894, 1989, 1223,
    1426, 11408, 3417, 2071, 1423, 876,
    1096, 8768,  2625, 1591, 1093, 673,

    2702, 21616, 6479, 3927, 2699, 1661,
    2102, 16816, 5039, 3054, 2099, 1292,
    1502, 12016, 3599, 2181, 1499, 923,
    1142, 9136,  2735, 1658, 1139, 701,

    2812, 22496, 6743, 4087, 2809, 1729,
    2216, 17728, 5313, 3220, 2219, 1362,
    1582, 12656, 3791, 2298, 1579, 972,
    1222, 9776,  2927, 1774, 1219, 750,

    2956, 23648, 7089, 4296, 2953, 1817,
    2334, 18672, 5596, 3391, 2331, 1435,
    1666, 13328, 3993, 2420, 1663, 1024,
    1276, 10208, 3057, 1852, 1273, 784
};
#define _QRCODE_DATA_CODEWORDS_HELPER(off, ver, ecl)      (qrcode_data_capacity_table[(off) + (QRCODE_VERSION(ver) - 1)*24 + (ecl)*6])
#define _QRCODE_DATA_BITS_HELPER(off, ver, ecl)           (qrcode_data_capacity_table[(off) + (QRCODE_VERSION(ver) - 1)*24 + (ecl)*6 + 1])
#define _QRCODE_DATA_CAPACITY_HELPER(off ,ver, ecl, mode) (qrcode_data_capacity_table[(off) + (QRCODE_VERSION(ver) - 1)*24 + (ecl)*6 + QRCODE_MODE(mode)])
#define QRCODE_DATA_CODEWORDS(ver, ecl)      (QRCODE_VERSION_VALID(ver) && QRCODE_ECL_VALID(ecl)                                 ? _QRCODE_DATA_CODEWORDS_HELPER(QRCODE_VERSION_IS_MICRO(ver) ? 0 : 96, ver, ecl) : -1)
#define QRCODE_DATA_BITS(ver, ecl)           (QRCODE_VERSION_VALID(ver) && QRCODE_ECL_VALID(ecl)                                 ? _QRCODE_DATA_BITS_HELPER(QRCODE_VERSION_IS_MICRO(ver)      ? 0 : 96, ver, ecl) : -1)
#define QRCODE_DATA_CAPACITY(ver, ecl, mode) (QRCODE_VERSION_VALID(ver) && QRCODE_ECL_VALID(ecl) && QRCODE_MODE_VALID_BASE(mode) ? _QRCODE_DATA_CAPACITY_HELPER(QRCODE_VERSION_IS_MICRO(ver)  ? 0 : 96, ver, ecl) : -1)

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

// 7.4.2, table 2, pg. 29
// bits 0-2:  Mode indicator length
// bits 3-6:  Terminator length
// bits 7-10: Mode indicator
#define QRCODE_MODE_LENGTH(mode)            (((mode) & 0b11100000000) >> 8)
#define QRCODE_MODE_VALUE(mode)             ((mode) & ((1 << QRCODE_MODE_LENGTH(mode)) - 1))
#define QRCODE_MODE_TERMINATOR_LENGTH(mode) (((mode) & 0b00011110000) >> 4)
static int qrcode_mode_info(int version, int mode){
    bool micro = QRCODE_VERSION_IS_MICRO(version);
    version = QRCODE_VERSION(version);
    bool alt = QRCODE_MODE_IS_ALT(mode);
    mode = QRCODE_MODE(mode);

    if (micro) switch (version){
        case 1: switch (mode){
            case QRCODE_MODE_NUMERIC: return 0b00000110000;
            default: return -1;
        }
        case 2: switch (mode){
            case QRCODE_MODE_NUMERIC:      return 0b00101010000;
            case QRCODE_MODE_ALPHANUMERIC: return 0b00101010001;
            default: return -1;
        }
        case 3: switch (mode){
            case QRCODE_MODE_NUMERIC:      return 0b01001110000;
            case QRCODE_MODE_ALPHANUMERIC: return 0b01001110001;
            case QRCODE_MODE_BYTE:         return 0b01001110010;
            case QRCODE_MODE_KANJI:        return 0b01001110011;
            default: return -1;
        }
        case 4: switch (mode){
            case QRCODE_MODE_NUMERIC:      return 0b01110010000;
            case QRCODE_MODE_ALPHANUMERIC: return 0b01110010001;
            case QRCODE_MODE_BYTE:         return 0b01110010010;
            case QRCODE_MODE_KANJI:        return 0b01110010011;
            default: return -1;
        }
        default: return -1;
    }
    switch (mode){
        case QRCODE_MODE_ECI:               return 0b10001000111;
        case QRCODE_MODE_NUMERIC:           return 0b10001000001;
        case QRCODE_MODE_ALPHANUMERIC:      return 0b10001000010;
        case QRCODE_MODE_BYTE:              return 0b10001000100;
        case QRCODE_MODE_KANJI:             return 0b10001001000;
        case QRCODE_MODE_STRUCTURED_APPEND: return 0b10001000011;
        case QRCODE_MODE_FNC1:              return alt ? 0b10001001001 : 0b10001000101;
        default: return -1;
    }
}

// 7.4.2, table 3, pg. 29
static int qrcode_cci_length(int version, int mode){
    bool micro = QRCODE_VERSION_IS_MICRO(version);
    version = QRCODE_VERSION(version);
    bool alt = QRCODE_MODE_IS_ALT(mode);
    mode = QRCODE_MODE(mode);

    if (micro) switch (version){
        case 1: switch (mode){
            case QRCODE_MODE_NUMERIC: return 3;
            default: return -1;
        }
        case 2: switch (mode){
            case QRCODE_MODE_NUMERIC:      return 4;
            case QRCODE_MODE_ALPHANUMERIC: return 3;
            default: return -1;
        }
        case 3: switch (mode){
            case QRCODE_MODE_NUMERIC:      return 5;
            case QRCODE_MODE_ALPHANUMERIC: return 4;
            case QRCODE_MODE_BYTE:         return 4;
            case QRCODE_MODE_KANJI:        return 3;
            default: return -1;
        }
        case 4: switch (mode){
            case QRCODE_MODE_NUMERIC:      return 6;
            case QRCODE_MODE_ALPHANUMERIC: return 5;
            case QRCODE_MODE_BYTE:         return 5;
            case QRCODE_MODE_KANJI:        return 4;
            default: return -1;
        }
        default: return -1;
    }
    switch (mode){
        case QRCODE_MODE_NUMERIC:      return version <= 9 ? 10 : (version <= 26  ? 12 : (version <= 40 ? 14 : -1));
        case QRCODE_MODE_ALPHANUMERIC: return version <= 9 ? 9  : (version <= 26  ? 11 : (version <= 40 ? 13 : -1));
        case QRCODE_MODE_BYTE:         return version <= 9 ? 8  : (version <= 26  ? 16 : (version <= 40 ? 16 : -1));
        case QRCODE_MODE_KANJI:        return version <= 9 ? 8  : (version <= 26  ? 10 : (version <= 40 ? 12 : -1));
        default: return -1;
    }
}

// 7.4.4, pg. 31
#define QRCODE_NUMERIC_LENGTH(version, dlen) (QRCODE_MODE_LENGTH(qrcode_mode_info(version, QRCODE_MODE_NUMERIC)) + qrcode_cci_length(version, QRCODE_MODE_NUMERIC) + 10*(dlen / 3) + ((4*(dlen % 3)) & 0b0111))
// Assumes valid utf8 string
static ssize_t qrcode_encode_numeric(const uint8_t* data, uint8_t* buf, size_t dlen, ssize_t bit, int version, int ecl){
    uint16_t val;
    ssize_t cci_len;
    ssize_t mode_info;
    ssize_t mode_ind;
    size_t mode_ind_len;
    size_t nbits;
    size_t rem;
    ssize_t bits;

    bits = QRCODE_DATA_BITS(version, ecl);
    if (bits < 0) return -1;

    cci_len = qrcode_cci_length(version, QRCODE_MODE_NUMERIC);
    if (cci_len < 0) return -1;
    mode_info = qrcode_mode_info(version, QRCODE_MODE_NUMERIC);
    if (mode_info < 0) return -1;
    mode_ind = QRCODE_MODE_VALUE(mode_info);
    mode_ind_len = QRCODE_MODE_LENGTH(mode_info);

    qrcode_write_bits(buf, &bit, mode_ind, mode_ind_len);
    qrcode_write_bits(buf, &bit, dlen, cci_len);

    for (size_t a = 0; a < dlen;){
        rem = dlen - a;
        if (rem >= 3){
            int8_t v1 = data[a];
            if (v1 < '0' || v1 > '9') return -1;
            int8_t v2 = data[a + 1];
            if (v2 < '0' || v2 > '9') return -1;
            int8_t v3 = data[a + 2];
            if (v3 < '0' || v3 > '9') return -1;
            val = (v1 - '0')*100 + (v2 - '0')*10 + (v3 - '0');
            nbits = 10;
            a += 3;
        }
        else if (rem == 2){
            int8_t v1 = data[a];
            if (v1 < '0' || v1 > '9') return -1;
            int8_t v2 = data[a + 1];
            if (v2 < '0' || v2 > '9') return -1;
            val = (v1 - '0')*10 + (v2 - '0');
            nbits = 7;
            a += 2;
        }
        else if (rem == 1){
            int8_t v1 = data[a];
            if (v1 < '0' || v1 > '9') return -1;
            val = (v1 - '0');
            nbits = 4;
            a += 1;
        }
        if (bit + nbits > bits) return -1;
        qrcode_write_bits(buf, &bit, val, nbits);
    }
    return bit;
}

// 7.4.5, pg. 32
#define QRCODE_ALPHANUMERIC_LENGTH(version, dlen) (QRCODE_MODE_LENGTH(qrcode_mode_info(version, QRCODE_MODE_ALPHANUMERIC)) + qrcode_cci_length(version, QRCODE_MODE_ALPHANUMERIC) + 11*(dlen / 2) + 6*(dlen % 2))
// Assumes valid utf8 string
static ssize_t qrcode_encode_alphanumeric(const uint8_t* data, uint8_t* buf, size_t dlen, ssize_t bit, int version, int ecl){    
    uint16_t val;
    ssize_t cci_len;
    ssize_t mode_info;
    ssize_t mode_ind;
    size_t mode_ind_len;
    size_t nbits;
    size_t rem;
    ssize_t bits;

    if (QRCODE_VERSION_IS_MICRO(version) && QRCODE_VERSION(version) == 1) return -1;
    bits = QRCODE_DATA_BITS(version, ecl);
    if (bits < 0) return -1;

    cci_len = qrcode_cci_length(version, QRCODE_MODE_ALPHANUMERIC);
    if (cci_len < 0) return -1;
    mode_info = qrcode_mode_info(version, QRCODE_MODE_ALPHANUMERIC);
    if (mode_info < 0) return -1;
    mode_ind = QRCODE_MODE_VALUE(mode_info);
    mode_ind_len = QRCODE_MODE_LENGTH(mode_info);

    qrcode_write_bits(buf, &bit, mode_ind, mode_ind_len);
    qrcode_write_bits(buf, &bit, dlen, cci_len);

    for (size_t a = 0; a < dlen;){
        rem = dlen - a;
        if (rem >= 2){
            int v1 = qrcode_alpha_to(data[a]);
            if (v1 < 0) return -1;
            int v2 = qrcode_alpha_to(data[a + 1]);
            if (v2 < 0) return -1;
            val = v1*45 + v2;
            nbits = 11;
            a += 2;
        }
        else{
            int v1 = qrcode_alpha_to(data[a]);
            if (v1 < 0) return -1;
            val = v1;
            nbits = 6;
            a += 1;
        }
        if (bit + nbits > bits) return -1;
        qrcode_write_bits(buf, &bit, val, nbits);
    }
    return bit;
}

// 7.4.10, pg. 37
static ssize_t qrcode_add_terminator(uint8_t* buf, ssize_t bit, int version, int ecl){
    ssize_t bits = QRCODE_DATA_BITS(version, ecl);
    if (bits < 0) return -1;

    ssize_t mode_info = qrcode_mode_info(version, QRCODE_MODE_NUMERIC);
    ssize_t term_len = QRCODE_MODE_TERMINATOR_LENGTH(mode_info);
    if (bit == bits) return bit;
    if (bits - bit <= term_len) term_len = bits - bit;
    if (bit + term_len > bits) return -1;
    qrcode_write_bits(buf, &bit, 0, term_len);
    return bit;
}

// 7.4.11, pg. 37
static ssize_t qrcode_add_padding(uint8_t* buf, ssize_t bit, int version, int ecl){
    ssize_t bits = QRCODE_DATA_BITS(version, ecl);
    if (bits < 0) return -1;

    if (bit % 8 != 0 && !(QRCODE_VERSION_IS_MICRO(version) && (QRCODE_VERSION(version) == 1 || QRCODE_VERSION(version) == 3))){
        if (bit + (8 - (bit % 8)) > bits) return -1;
        qrcode_write_bits(buf, &bit, 0, 8 - (bit % 8));
    }
    if (bits < 0) return -1;
    size_t padding = (bits - bit) / 8;
    size_t rem = (bits - bit) % 8;
    for (size_t a = 0; a < padding; a++){
        if (bit + 8 > bits) return -1;
        if (a % 2 == 0) qrcode_write_bits(buf, &bit, 0b11101100, 8);
        else qrcode_write_bits(buf, &bit, 0b00010001, 8);
    }
    if (rem && QRCODE_VERSION_IS_MICRO(version) && (QRCODE_VERSION(version) == 1 || QRCODE_VERSION(version) == 3)){
        if (bit + 4 > bits) return -1;
        if (padding % 2 == 0) qrcode_write_bits(buf, &bit, 0b1110, 4);
        else qrcode_write_bits(buf, &bit, 0b0001, 4);
    }
    return bit;
}

#endif