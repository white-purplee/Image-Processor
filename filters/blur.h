#pragma once

#include "base_filter.h"
#include <cmath>

class Blur : public BaseFilterWithMatrix {
public:
    Blur();
    explicit Blur(double sigma);
    void Apply(Image& image) override;
    double GetValue(size_t dx) const;

private:
    double sigma_;
};