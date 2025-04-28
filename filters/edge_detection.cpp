#include "edge_detection.h"
#include "gray_scale.h"

EdgeDetection::EdgeDetection(double threshold) {
    threshold_ = threshold;
    matrix_ = std::vector<std::vector<double>>{{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
}

void EdgeDetection::Apply(Image& image) {
    GrayScale gs;
    gs.Apply(image);
    Image new_image(image.GetHeight(), image.GetWidth());
    for (int32_t row = 0; row < static_cast<int32_t>(image.GetHeight()); ++row) {
        for (int32_t column = 0; column < static_cast<int32_t>(image.GetWidth()); ++column) {
            const double total = 1.0;
            Pixel new_pixel =
                matrix_[0][0] * image.GetPixel(row - 1, column - 1) + matrix_[0][1] * image.GetPixel(row - 1, column) +
                matrix_[0][2] * image.GetPixel(row - 1, column + 1) + matrix_[1][0] * image.GetPixel(row, column - 1) +
                matrix_[1][1] * image.GetPixel(row, column) + matrix_[1][2] * image.GetPixel(row, column + 1) +
                matrix_[2][0] * image.GetPixel(row + 1, column - 1) + matrix_[2][1] * image.GetPixel(row + 1, column) +
                matrix_[2][2] * image.GetPixel(row + 1, column + 1);
            double red = NAN;
            double green = NAN;
            double blue = NAN;
            new_pixel.Get(red, green, blue);
            if (red > threshold_) {
                red = green = blue = total;
            } else {
                red = green = blue = 0;
            }
            new_image.GetPixel(row, column).Set(red, green, blue);
        }
    }
    image = new_image;
}