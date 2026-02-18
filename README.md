# libqrcode

A library for encoding/decoding ISO/IEC 18004-2024 compliant QR codes

## Description

The purpose of this project is to provide a simple interface for encoding/decoding QR codes. The intent is for all portions of the specificiation to be supported.

## TODO
- [ ] Error correction codeword generation
- [ ] Data-ECC interleaving
- [ ] Basic grid generation (no data)
- [ ] Codeword placement in grid
- [ ] Support all data modes
    - [x] Numeric, encode
    - [ ] Numeric, decode
    - [x] Alphanumeric, encode
    - [ ] Alphanumeric, decode
    - [x] Byte, encode
    - [ ] Byte, decode
    - [ ] Kanji, encode
    - [ ] Kanji, decode
- [ ] Support all auxillary modes
    - [ ] FNC1, encode
    - [ ] FNC1, decode
    - [ ] ECI, encode
    - [ ] ECI, decode
    - [ ] Structured append, encode
    - [ ] Structured append, decode