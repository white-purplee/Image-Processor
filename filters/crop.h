#pragma once

#include "base_filter.h"

class Crop : public BaseFilter {
public:
    Crop(size_t height, size_t width);
    void Apply(Image& image) override;

private:
    size_t height_ = 0;
    size_t width_ = 0;
};