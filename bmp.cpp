#include "bmp.h"
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>

Image BMPRead(const std::string& in_path) {
    std::ifstream file(in_path, std::ios::binary);
    if (!file.is_open()) {
        throw BMPException("Failed to open input file");
    }

    FileHeader file_header;
    file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    const uint16_t bm = 0x4D42;
    if (file_header.bf_type != bm) {
        throw BMPException("Not a valid BMP file");
    }

    ImageHeader image_header;
    file.read(reinterpret_cast<char*>(&image_header), sizeof(image_header));
    const uint32_t size = 40;
    if (image_header.bi_size != size) {
        throw BMPException("Unsupported BMP format");
    }
    if (image_header.bi_compression != 0) {
        throw BMPException("Compressed BMP not supported");
    }
    const uint16_t bit_count = 24;
    if (image_header.bi_bit_count != bit_count) {
        throw BMPException("Only 24-bit BMPs are supported");
    }

    const uint32_t width = image_header.bi_width;
    const uint32_t height = image_header.bi_height;

    const uint32_t bytes_per_pixel = 3;
    const uint32_t row_size = ((width * bytes_per_pixel + 3) / 4) * 4;
    file.seekg(file_header.bf_offbits, std::ios::beg);

    Image image(height, width);
    std::vector<uint8_t> row(row_size);

    for (uint32_t y = 0; y < height; ++y) {
        file.read(reinterpret_cast<char*>(row.data()), row_size);

        const uint32_t image_y = height - 1 - y;

        for (uint32_t x = 0; x < width; ++x) {
            const uint8_t* pixel = row.data() + x * bytes_per_pixel;
            uint8_t blue = pixel[0];
            uint8_t green = pixel[1];
            uint8_t red = pixel[2];
            image.GetPixel(static_cast<size_t>(image_y), static_cast<size_t>(x)).Set(red, green, blue);
        }
    }

    return image;
}

void BMPWrite(const Image& image, const std::string& out_path) {
    std::ofstream file(out_path, std::ios::binary);
    if (!file.is_open()) {
        throw BMPException("Failed to open output file");
    }

    const uint32_t width = static_cast<int32_t>(image.GetWidth());
    const uint32_t height = static_cast<int32_t>(image.GetHeight());
    const uint16_t bits_per_pixel = 24;
    const uint32_t bytes_per_pixel = 3;

    const uint32_t row_size = ((width * bytes_per_pixel + 3) / 4) * 4;

    FileHeader file_header;
    const uint16_t bm = 0x4D42;
    file_header.bf_type = bm;
    file_header.bf_size = sizeof(FileHeader) + sizeof(ImageHeader) + row_size * height;
    file_header.bf_reserved1 = 0;
    file_header.bf_reserved2 = 0;
    file_header.bf_offbits = sizeof(FileHeader) + sizeof(ImageHeader);

    ImageHeader image_header;
    const uint32_t size = 40;
    image_header.bi_size = size;
    image_header.bi_width = width;
    image_header.bi_height = height;
    image_header.bi_planes = 1;
    image_header.bi_bit_count = bits_per_pixel;
    image_header.bi_compression = 0;
    image_header.bi_size_image = row_size * height;
    image_header.bi_xpels_per_meter = 0;
    image_header.bi_ypels_per_meter = 0;
    image_header.bi_clr_used = 0;
    image_header.bi_clr_important = 0;

    file.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
    file.write(reinterpret_cast<const char*>(&image_header), sizeof(image_header));

    std::vector<uint8_t> row(row_size, 0);

    for (uint32_t y = 0; y < height; ++y) {
        const uint32_t image_y = height - 1 - y;
        for (uint32_t x = 0; x < width; ++x) {
            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;
            image.GetPixel(static_cast<size_t>(image_y), static_cast<size_t>(x)).Get(red, green, blue);
            uint8_t* pixel = row.data() + x * bytes_per_pixel;
            pixel[0] = blue;
            pixel[1] = green;
            pixel[2] = red;
        }
        file.write(reinterpret_cast<const char*>(row.data()), row_size);
    }
}