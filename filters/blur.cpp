#include "blur.h"

Blur::Blur() {
}

Blur::Blur(double sigma) {
    sigma_ = sigma;
}

double Blur::GetValue(size_t dx) const {
    const double exponent = -(static_cast<double>(dx) * static_cast<double>(dx)) / (2.0 * sigma_ * sigma_);
    const double coef = 1.0 / std::sqrt(2.0 * M_PI * sigma_ * sigma_);
    return coef * std::exp(exponent);
}

void Blur::Apply(Image& image) {
    std::vector<double> coefs(std::max(image.GetHeight(), image.GetWidth()) + 1, 0);
    for (size_t i = 0; i < coefs.size(); ++i) {
        coefs[i] = GetValue(i);
    }

    const size_t threshold = 4;
    Image new_image(image.GetHeight(), image.GetWidth());
    for (size_t row = 0; row < image.GetHeight(); ++row) {
        for (size_t column = 0; column < image.GetWidth(); ++column) {
            Pixel new_pixel = coefs[0] * image.GetPixel(row, column);
            double coef_sum = coefs[0];
            for (size_t dx = 1; static_cast<double>(dx) < threshold * sigma_; ++dx) {
                if (row >= dx) {
                    new_pixel = new_pixel + coefs[dx] * image.GetPixel(row - dx, column);
                    coef_sum += coefs[dx];
                }
                if (row + dx < image.GetHeight()) {
                    new_pixel = new_pixel + coefs[dx] * image.GetPixel(row + dx, column);
                    coef_sum += coefs[dx];
                }
            }
            new_pixel = (1.0 / coef_sum) * new_pixel;
            new_image.GetPixel(row, column).Set(new_pixel);
        }
    }
    image = new_image;
    for (size_t row = 0; row < image.GetHeight(); ++row) {
        for (size_t column = 0; column < image.GetWidth(); ++column) {
            Pixel new_pixel = coefs[0] * image.GetPixel(row, column);
            double coef_sum = coefs[0];
            for (size_t dx = 1; static_cast<double>(dx) < threshold * sigma_; ++dx) {
                if (column >= dx) {
                    new_pixel = new_pixel + coefs[dx] * image.GetPixel(row, column - dx);
                    coef_sum += coefs[dx];
                }
                if (column + dx < image.GetWidth()) {
                    new_pixel = new_pixel + coefs[dx] * image.GetPixel(row, column + dx);
                    coef_sum += coefs[dx];
                }
            }
            new_pixel = (1.0 / coef_sum) * new_pixel;
            new_image.GetPixel(row, column).Set(new_pixel);
        }
    }
    image = new_image;
}