#include "crop.h"

Crop::Crop(size_t height, size_t width) : height_(height), width_(width) {
}

void Crop::Apply(Image& image) {
    image.SetHeight(height_);
    image.SetWidth(width_);
}