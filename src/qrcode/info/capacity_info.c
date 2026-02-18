#include "qrcode/info/capacity_info.h"

#include "qrcode/validation.h"
#include "qrcode/common.h"
#include "qrcode/error.h"

#include <stdbool.h>
#include <stddef.h>

const struct qrcode_capacity_info qrcode_capacity_info_table[176] = {
    {3, 5, 0, 0, 0, true},
    {},
    {},
    {},

    {5, 10, 6, 0, 0, false},
    {4, 8,  5, 0, 0, false},
    {},
    {},

    {11, 23, 14, 9,  6, true},
    {9,  18, 11, 7,  4, true},
    {},
    {},

    {16, 35, 21, 15, 9, false},
    {14, 30, 18, 13, 8, false},
    {10, 21, 13, 9,  5, false},
    {},
    
    {19, 41, 25, 17, 10, false},
    {16, 34, 20, 14, 8,  false},
    {13, 27, 16, 11, 7,  false},
    {9,  17, 10, 7,  4,  false},
    
    {34, 77, 47, 32, 20, false},
    {28, 63, 38, 26, 16, false},
    {22, 48, 29, 20, 12, false},
    {16, 34, 20, 14, 8,  false},

    {55, 127, 77, 53, 32, false},
    {44, 101, 61, 42, 26, false},
    {34, 77,  47, 32, 20, false},
    {26, 58,  35, 24, 15, false},

    {80, 187, 114, 78, 48, false},
    {64, 149, 90,  62, 38, false},
    {48, 111, 67,  46, 28, false},
    {36, 82,  50,  34, 21, false},

    {108, 255, 154, 106, 65, false},
    {86,  202, 122, 84,  52, false},
    {62,  144, 87,  60,  37, false},
    {46,  106, 64,  44,  27, false},

    {136, 322, 196, 134, 82, false},
    {108, 255, 154, 106, 65, false},
    {76,  178, 108, 74,  45, false},
    {60,  139, 84,  58,  36, false},

    {156, 370, 224, 154, 95, false},
    {124, 293, 178, 122, 75, false},
    {88,  207, 125, 86,  53, false},
    {66,  154, 93,  64,  39, false},

    {194, 461, 279, 192, 118, false},
    {154, 365, 221, 152, 93,  false},
    {110, 259, 157, 108, 66,  false},
    {86,  202, 122, 84,  52,  false},

    {232, 552, 335, 230, 141, false},
    {182, 432, 262, 180, 111, false},
    {132, 312, 189, 130, 80,  false},
    {100, 235, 143, 98,  60,  false},

    {274, 652, 395, 271, 167, false},
    {216, 513, 311, 213, 131, false},
    {154, 364, 221, 151, 93,  false},
    {122, 288, 174, 119, 74,  false},

    {324, 772, 468, 321, 198, false},
    {254, 604, 366, 251, 155, false},
    {180, 427, 259, 177, 109, false},
    {140, 331, 200, 137, 85,  false},

    {370, 883, 535, 367, 226, false},
    {290, 691, 419, 287, 177, false},
    {206, 489, 296, 203, 125, false},
    {158, 374, 227, 155, 96,  false},

    {428, 1022, 619, 425, 262, false},
    {334, 796,  483, 331, 204, false},
    {244, 580,  352, 241, 149, false},
    {180, 427,  259, 177, 109, false},

    {461, 1101, 667, 458, 282, false},
    {365, 871,  528, 362, 223, false},
    {261, 621,  376, 258, 159, false},
    {197, 468,  283, 194, 120, false},

    {523, 1250, 758, 520, 320, false},
    {415, 991,  600, 412, 254, false},
    {295, 703,  426, 292, 180, false},
    {223, 530,  321, 220, 136, false},

    {589, 1408, 854, 586, 361, false},
    {453, 1082, 656, 450, 277, false},
    {325, 755,  470, 322, 198, false},
    {253, 602,  365, 250, 154, false},

    {647, 1548, 938, 644, 397, false},
    {507, 1212, 734, 504, 310, false},
    {367, 876,  531, 364, 224, false},
    {313, 674,  408, 280, 173, false},

    {795, 1725, 1046, 718, 442, false},
    {563, 1346, 816,  560, 345, false},
    {397, 948,  574,  394, 243, false},
    {313, 746,  452,  310, 191, false},

    {795, 1903, 1153, 792, 488, false},
    {627, 1500, 909,  624, 384, false},
    {445, 1063, 644,  442, 272, false},
    {341, 813,  493,  338, 208, false},

    {861, 2061, 1249, 858, 528, false},
    {669, 1600, 970,  666, 410, false},
    {485, 1159, 702,  482, 297, false},
    {385, 919,  557,  382, 235, false},
    
    {932, 2232, 1352, 929, 572, false},
    {714, 1708, 1035, 711, 438, false},
    {512, 1224, 742,  509, 314, false},
    {406, 969,  587,  403, 248, false},

    {1006, 2409, 1460, 1003, 618, false},
    {782,  1872, 1134, 779,  480, false},
    {568,  1358, 823,  565,  348, false},
    {442,  1056, 640,  439,  270, false},

    {1094, 2620, 1588, 1091, 672, false},
    {860,  2059, 1248, 857,  528, false},
    {614,  1468, 890,  611,  376, false},
    {464,  1108, 672,  461,  284, false},

    {1174, 2812, 1704, 1171, 721, false},
    {914,  2188, 1326, 911,  561, false},
    {664,  1588, 963,  661,  407, false},
    {514,  1228, 744,  511,  315, false},

    {1276, 3057, 1853, 1273, 784, false},
    {1000, 2395, 1451, 997,  614, false},
    {718,  1718, 1041, 715,  440, false},
    {538,  1286, 779,  535,  330, false},

    {1370, 3283, 1990, 1367, 842, false},
    {1062, 2544, 1542, 1059, 652, false},
    {754,  1804, 1094, 751,  462, false},
    {596,  1425, 864,  593,  365, false},

    {1468, 3517, 2132, 1465, 902, false},
    {1128, 2701, 1637, 1125, 692, false},
    {808,  1933, 1172, 805,  496, false},
    {628,  1501, 910,  625,  385, false},

    {1531, 3669, 2223, 1528, 940, false},
    {1193, 2857, 1732, 1190, 732, false},
    {871,  2085, 1263, 868,  534, false},
    {661,  1581, 958,  658,  405, false},

    {1631, 3909, 2369, 1628, 1002, false},
    {1267, 3035, 1839, 1264, 778,  false},
    {911,  2181, 1322, 908,  559,  false},
    {701,  1677, 1016, 698,  430,  false},

    {1735, 4158, 2520, 1732, 1066, false},
    {1373, 3289, 1994, 1370, 843,  false},
    {985,  2358, 1429, 982,  604,  false},
    {745,  1782, 1080, 742,  457,  false},

    {1843, 4417, 2677, 1840, 1132, false},
    {1455, 3486, 2113, 1452, 894,  false},
    {1033, 2473, 1499, 1030, 634,  false},
    {793,  1897, 1150, 790,  486,  false},

    {1955, 4686, 2840, 1952, 1201, false},
    {1541, 3693, 2238, 1538, 947,  false},
    {1115, 2670, 1618, 1112, 684,  false},
    {845,  2022, 1226, 842,  518,  false},

    {2071, 4965, 3009, 2068, 1273, false},
    {1631, 3909, 2369, 1628, 1002, false},
    {1171, 2805, 1700, 1168, 719,  false},
    {901,  2157, 1307, 898,  553,  false},

    {2191, 5253, 3183, 2188, 1347, false},
    {1725, 4134, 2506, 1722, 1060, false},
    {1231, 2949, 1787, 1228, 756,  false},
    {961,  2301, 1394, 958,  590,  false},

    {2306, 5529, 3351, 2303, 1417, false},
    {1812, 4343, 2632, 1809, 1113, false},
    {1286, 2081, 1867, 1283, 790,  false},
    {986,  2361, 1431, 983,  605,  false},

    {2434, 5836, 3537, 2431, 1496, false},
    {1914, 4588, 2780, 1911, 1176, false},
    {1354, 3244, 1966, 1351, 832,  false},
    {1054, 2524, 1530, 1051, 647,  false},

    {2566, 6153, 3729, 2563, 1577, false},
    {1992, 4775, 2894, 1989, 1223, false},
    {1426, 3417, 2071, 1423, 876,  false},
    {1096, 2625, 1591, 1093, 673,  false},

    {2702, 6479, 3927, 2699, 1661, false},
    {2102, 5039, 3054, 2099, 1292, false},
    {1502, 3599, 2181, 1499, 923,  false},
    {1142, 2735, 1658, 1139, 701,  false},

    {2812, 6743, 4087, 2809, 1729, false},
    {2216, 5313, 3220, 2219, 1362, false},
    {1582, 3791, 2298, 1579, 972,  false},
    {1222, 2927, 1774, 1219, 750,  false},

    {2956, 7089, 4296, 2953, 1817, false},
    {2334, 5596, 3391, 2331, 1435, false},
    {1666, 3993, 2420, 1663, 1024, false},
    {1276, 3057, 1852, 1273, 784,  false},
};

int qrcode_capacity_info(int ver, int ecl, int mode, struct qrcode_capacity_info* out_info){
    if (!QRCODE_VALID_VERSION(ver)) return QRCODE_ERROR(QRCODE_ERROR_VERSION, -1);
    if (!QRCODE_VALID_ECL(ecl)) return QRCODE_ERROR(QRCODE_ERROR_ECL, -1);

    size_t offset = 16;
    if (QRCODE_IS_MICRO(ver)){
        ver = QRCODE_VERSION_BASE(ver);
        if (ver == 1){
            if (ecl != QRCODE_ECL_L) return QRCODE_ERROR(QRCODE_ERROR_COMBO | QRCODE_ERROR_VERSION | QRCODE_ERROR_ECL, -1);
            if (mode > QRCODE_ENCODING_NUMERIC) return QRCODE_ERROR(QRCODE_ERROR_COMBO | QRCODE_ERROR_VERSION | QRCODE_ERROR_ENCODING, -1);
        }
        if (ver == 2){
            if (ecl > QRCODE_ECL_M) return QRCODE_ERROR(QRCODE_ERROR_COMBO | QRCODE_ERROR_VERSION | QRCODE_ERROR_ECL, -1);
            if (mode > QRCODE_ENCODING_ALPHANUMERIC) return QRCODE_ERROR(QRCODE_ERROR_COMBO | QRCODE_ERROR_VERSION | QRCODE_ERROR_ENCODING, -1);
        }
        if (ver == 3 && ecl > QRCODE_ECL_M) return QRCODE_ERROR(QRCODE_ERROR_COMBO | QRCODE_ERROR_VERSION | QRCODE_ERROR_ECL, -1);
        if (ver == 4 && ecl > QRCODE_ECL_Q) return QRCODE_ERROR(QRCODE_ERROR_COMBO | QRCODE_ERROR_VERSION | QRCODE_ERROR_ECL, -1);
        offset = 0;
    }
    
    *out_info = qrcode_capacity_info_table[offset + (ver - 1)*4 + ecl];
    return 0;
}