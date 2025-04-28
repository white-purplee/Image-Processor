#include "base_filter.h"

void BaseFilterWithMatrix::Apply(Image& image) {
    for (int32_t row = 0; row < static_cast<int32_t>(image.GetHeight()); ++row) {
        for (int32_t column = 0; column < static_cast<int32_t>(image.GetWidth()); ++column) {
            Pixel new_pixel =
                matrix_[0][0] * image.GetPixel(row - 1, column - 1) + matrix_[0][1] * image.GetPixel(row - 1, column) +
                matrix_[0][2] * image.GetPixel(row - 1, column + 1) + matrix_[1][0] * image.GetPixel(row, column - 1) +
                matrix_[1][1] * image.GetPixel(row, column) + matrix_[1][2] * image.GetPixel(row, column + 1) +
                matrix_[2][0] * image.GetPixel(row + 1, column - 1) + matrix_[2][1] * image.GetPixel(row + 1, column) +
                matrix_[2][2] * image.GetPixel(row + 1, column + 1);
            image.GetPixel(row, column).Set(new_pixel);
        }
    }
}