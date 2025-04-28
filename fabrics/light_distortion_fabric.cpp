#include "light_distortion_fabric.h"

#include "../filters/light_distortion.h"

std::shared_ptr<BaseFilter> LightDistortionFabric::Create(const std::vector<std::string>& input_params) {
    if (input_params.size() != 3) {
        throw FilterException("Wrong arguments number for -dist, should be 2");
    }
    double center_x = NAN;
    double center_y = NAN;
    double strength = NAN;
    try {
        center_x = std::stod(input_params[0]);
        center_y = std::stod(input_params[1]);
        strength = std::stod(input_params[2]);
    } catch (const std::exception& ex) {
        throw FilterException("Wrong argument type for -dist, should be double");
    }
    return std::make_shared<LightDistortion>(center_x, center_y, strength);
}