#include <string>

#include "crop_fabric.h"

#include "../filters/crop.h"

std::shared_ptr<BaseFilter> CropFabric::Create(const std::vector<std::string>& input_params) {
    if (input_params.size() != 2) {
        throw FilterException("Wrong arguments number for -crop, should be 2");
    }
    size_t height = 0;
    size_t width = 0;
    try {
        height = static_cast<size_t>(std::stoi(input_params[0]));
        width = static_cast<size_t>(std::stoi(input_params[1]));
    } catch (const std::exception& ex) {
        throw FilterException("Wrong argument type for -crop, should be positive integer");
    }
    return std::make_shared<Crop>(height, width);
}