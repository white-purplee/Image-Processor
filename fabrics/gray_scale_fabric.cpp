#include <string>

#include "gray_scale_fabric.h"

#include "../filters/gray_scale.h"

std::shared_ptr<BaseFilter> GrayScaleFabric::Create(const std::vector<std::string>& input_params) {
    if (!input_params.empty()) {
        throw FilterException("Wrong arguments number for -gs, should be 0");
    }
    return std::make_shared<GrayScale>();
}