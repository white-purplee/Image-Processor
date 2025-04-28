#include "image.h"

Pixel::Pixel() : red_(0), green_(0), blue_(0) {
}

Pixel::Pixel(double red, double green, double blue) : red_(red), green_(green), blue_(blue) {
}

void Pixel::Set(uint8_t red, uint8_t green, uint8_t blue) {
    const double total = 255.0;
    red_ = std::max(0.0, std::min(total, static_cast<double>(red))) / total;
    green_ = std::max(0.0, std::min(total, static_cast<double>(green))) / total;
    blue_ = std::max(0.0, std::min(total, static_cast<double>(blue))) / total;
}

void Pixel::Set(double red, double green, double blue) {
    const double total = 1.0;
    red_ = std::max(0.0, std::min(total, red));
    green_ = std::max(0.0, std::min(total, green));
    blue_ = std::max(0.0, std::min(total, blue));
}

void Pixel::Set(Pixel& p) {
    double red = NAN;
    double green = NAN;
    double blue = NAN;
    p.Get(red, green, blue);
    const double total = 1.0;
    red = std::max(0.0, std::min(total, red));
    green = std::max(0.0, std::min(total, green));
    blue = std::max(0.0, std::min(total, blue));
    Set(red, green, blue);
}

void Pixel::SetCopy(Pixel p) {
    double red = NAN;
    double green = NAN;
    double blue = NAN;
    p.Get(red, green, blue);
    const double total = 1.0;
    red = std::max(0.0, std::min(total, red));
    green = std::max(0.0, std::min(total, green));
    blue = std::max(0.0, std::min(total, blue));
    Set(red, green, blue);
}

const void Pixel::Get(uint8_t& red, uint8_t& green, uint8_t& blue) const {
    const double total = 255.0;
    red = static_cast<uint8_t>(round(red_ * total));
    green = static_cast<uint8_t>(round(green_ * total));
    blue = static_cast<uint8_t>(round(blue_ * total));
}

const void Pixel::Get(double& red, double& green, double& blue) const {
    red = red_;
    green = green_;
    blue = blue_;
}

Pixel operator*(double x, const Pixel& p) {
    return Pixel(p.red_ * x, p.green_ * x, p.blue_ * x);
}

Pixel operator+(const Pixel& p1, const Pixel& p2) {
    return Pixel(p1.red_ + p2.red_, p1.green_ + p2.green_, p1.blue_ + p2.blue_);
}

void Pixel::Print() const {
    std::cerr << red_ << " " << blue_ << " " << green_ << '\n';
}

Image::Image() {
}

Image::Image(std::vector<std::vector<Pixel>> pixels) : pixels_(pixels) {
}

Image::Image(size_t height, size_t width) : height_(height), width_(width) {
    pixels_.resize(height, std::vector<Pixel>(width));
}

Pixel& Image::GetPixel(int32_t row, int32_t column) {
    if (row < 0) {
        row = 0;
    }
    if (column < 0) {
        column = 0;
    }
    if (row >= static_cast<int32_t>(height_)) {
        row = static_cast<int32_t>(height_) - 1;
    }
    if (column >= static_cast<int32_t>(width_)) {
        column = static_cast<int32_t>(width_) - 1;
    }
    return pixels_[row][column];
}

const Pixel& Image::GetPixel(int32_t row, int32_t column) const {
    if (row < 0) {
        row = 0;
    }
    if (column < 0) {
        column = 0;
    }
    if (row >= static_cast<int32_t>(height_)) {
        row = static_cast<int32_t>(height_) - 1;
    }
    if (column >= static_cast<int32_t>(width_)) {
        column = static_cast<int32_t>(width_) - 1;
    }
    return pixels_[row][column];
}

Pixel& Image::GetPixel(size_t row, size_t column) {
    if (row >= height_) {
        row = height_ - 1;
    }
    if (column >= width_) {
        column = width_ - 1;
    }
    return pixels_[row][column];
}

const Pixel& Image::GetPixel(size_t row, size_t column) const {
    if (row >= height_) {
        row = height_ - 1;
    }
    if (column >= width_) {
        column = width_ - 1;
    }
    return pixels_[row][column];
}

Pixel Image::GetPixelInBetween(double x, double y) {
    int32_t x1 = static_cast<int32_t>(x);
    int32_t y1 = static_cast<int32_t>(y);
    int32_t x2 = x1 + 1;
    int32_t y2 = y1 + 1;

    double dx = x - x1;
    double dy = y - y1;

    return Pixel((1 - dx) * (1 - dy) * GetPixel(x1, y1) + dx * (1 - dy) * GetPixel(x2, y1) +
                 (1 - dx) * dy * GetPixel(x1, y2) + dx * dy * GetPixel(x2, y2));
}

const size_t Image::GetWidth() const {
    return width_;
}

const size_t Image::GetHeight() const {
    return height_;
}

void Image::SetHeight(size_t height) {
    if (height < height_) {
        pixels_.resize(height);
        height_ = height;
    }
}

void Image::SetWidth(size_t width) {
    if (width < width_) {
        for (size_t i = 0; i < height_; ++i) {
            pixels_[i].resize(width);
        }
        width_ = width;
    }
}