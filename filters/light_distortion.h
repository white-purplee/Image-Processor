#pragma once

#include "base_filter.h"
#include <cmath>

class LightDistortion : public BaseFilter {
public:
    LightDistortion(double center_x, double center_y, double strength);
    void Apply(Image& image) override;

private:
    double center_x_;
    double center_y_;
    double strength_;
};