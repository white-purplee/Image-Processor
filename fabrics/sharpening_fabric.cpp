#include "sharpening_fabric.h"

#include "../filters/sharpening.h"

std::shared_ptr<BaseFilter> SharpeningFabric::Create(const std::vector<std::string>& input_params) {
    if (!input_params.empty()) {
        throw FilterException("Wrong arguments number for -edge, should be 0");
    }
    return std::make_shared<Sharpening>();
}