#include "light_distortion.h"

LightDistortion::LightDistortion(double center_x, double center_y, double strength)
    : center_x_(center_x), center_y_(center_y), strength_(strength) {
}

void LightDistortion::Apply(Image& image) {
    Image new_image(image.GetHeight(), image.GetWidth());

    double center_x = center_x_ * static_cast<double>(image.GetHeight());
    double center_y = center_y_ * static_cast<double>(image.GetWidth());
    for (size_t x = 0; x < image.GetHeight(); ++x) {
        for (size_t y = 0; y < image.GetWidth(); ++y) {
            double dx = static_cast<double>(x) - center_x;
            double dy = static_cast<double>(y) - center_y;
            double radius = std::sqrt(dx * dx + dy * dy);
            double angle = std::atan2(dy, dx);

            angle += strength_ * radius / 100.0;
            double new_x = center_x + radius * std::cos(angle);
            double new_y = center_y + radius * std::sin(angle);
            new_image.GetPixel(x, y).SetCopy(image.GetPixelInBetween(new_x, new_y));
        }
    }
    image = new_image;
}