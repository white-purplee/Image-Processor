#pragma once

#include <vector>
#include <cmath>
#include <cstdint>
#include <iostream>

struct Pixel {
public:
    Pixel();
    Pixel(double red, double green, double blue);
    void Set(uint8_t red, uint8_t green, uint8_t blue);
    void Set(double red, double green, double blue);
    void Set(Pixel& p);
    void SetCopy(Pixel p);
    const void Get(uint8_t& red, uint8_t& green, uint8_t& blue) const;
    const void Get(double& red, double& green, double& blue) const;
    void Print() const;
    double red_;
    double green_;
    double blue_;
};

Pixel operator*(double x, const Pixel& p);
Pixel operator+(const Pixel& p1, const Pixel& p2);

class Image {
public:
    Image();
    explicit Image(std::vector<std::vector<Pixel>> pixels);
    Image(size_t height, size_t width);
    Pixel& GetPixel(int32_t row, int32_t column);
    const Pixel& GetPixel(int32_t row, int32_t column) const;
    Pixel& GetPixel(size_t row, size_t column);
    const Pixel& GetPixel(size_t row, size_t column) const;
    Pixel GetPixelInBetween(double row, double column);

    const size_t GetWidth() const;
    const size_t GetHeight() const;
    void SetHeight(size_t height);
    void SetWidth(size_t width);

private:
    size_t height_;
    size_t width_;
    std::vector<std::vector<Pixel>> pixels_;
};