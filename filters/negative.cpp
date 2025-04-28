#include "negative.h"

Negative::Negative() {
}

void Negative::Apply(Image& image) {
    for (size_t row = 0; row < image.GetHeight(); ++row) {
        for (size_t column = 0; column < image.GetWidth(); ++column) {
            double red = NAN;
            double green = NAN;
            double blue = NAN;
            image.GetPixel(row, column).Get(red, green, blue);
            image.GetPixel(row, column).Set(1.0 - red, 1.0 - green, 1.0 - blue);
        }
    }
}