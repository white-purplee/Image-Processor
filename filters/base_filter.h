#pragma once

#include "../image.h"
#include "../exception.h"

#include <vector>

class BaseFilter {
public:
    virtual void Apply(Image& image) = 0;
    virtual ~BaseFilter() = default;
};

class BaseFilterWithMatrix : public BaseFilter {
public:
    void Apply(Image& image) override;

protected:
    std::vector<std::vector<double>> matrix_;
};