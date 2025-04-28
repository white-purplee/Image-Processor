#pragma once
#include <cstdint>
#include <string>
#include "image.h"
#include "exception.h"

#pragma pack(push, 1)
struct FileHeader {
    uint16_t bf_type;
    uint32_t bf_size;
    uint16_t bf_reserved1;
    uint16_t bf_reserved2;
    uint32_t bf_offbits;
};

struct ImageHeader {
    uint32_t bi_size;
    uint32_t bi_width;
    uint32_t bi_height;
    uint16_t bi_planes;
    uint16_t bi_bit_count;
    uint32_t bi_compression;
    uint32_t bi_size_image;
    int32_t bi_xpels_per_meter;
    int32_t bi_ypels_per_meter;
    uint32_t bi_clr_used;
    uint32_t bi_clr_important;
};
#pragma pack(pop)

Image BMPRead(const std::string& in_path);
void BMPWrite(const Image& image, const std::string& out_path);