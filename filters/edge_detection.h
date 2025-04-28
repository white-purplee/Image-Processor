#pragma once

#include "base_filter.h"

class EdgeDetection : public BaseFilterWithMatrix {
public:
    explicit EdgeDetection(double threshold);
    void Apply(Image& image) override;

private:
    double threshold_;
};