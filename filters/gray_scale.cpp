#include "gray_scale.h"

GrayScale::GrayScale() {
}

void GrayScale::Apply(Image& image) {
    for (size_t row = 0; row < image.GetHeight(); ++row) {
        for (size_t column = 0; column < image.GetWidth(); ++column) {
            double red = NAN;
            double green = NAN;
            double blue = NAN;
            image.GetPixel(row, column).Get(red, green, blue);
            const double red_coef = 0.299;
            const double green_coef = 0.587;
            const double blue_coef = 0.114;
            double new_color = red_coef * red + green_coef * green + blue_coef * blue;
            image.GetPixel(row, column).Set(new_color, new_color, new_color);
        }
    }
}