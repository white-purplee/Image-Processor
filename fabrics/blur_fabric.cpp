#include "blur_fabric.h"

#include "../filters/blur.h"

std::shared_ptr<BaseFilter> BlurFabric::Create(const std::vector<std::string>& input_params) {
    if (input_params.size() != 1) {
        throw FilterException("Wrong arguments number for -blur, should be 1");
    }
    double sigma = NAN;
    try {
        sigma = std::stod(input_params[0]);
    } catch (const std::exception& ex) {
        throw FilterException("Wrong argument type for -blur, should be double");
    }
    return std::make_shared<Blur>(sigma);
}