#include "negative_fabric.h"

#include "../filters/negative.h"

std::shared_ptr<BaseFilter> NegativeFabric::Create(const std::vector<std::string>& input_params) {
    if (!input_params.empty()) {
        throw FilterException("Wrong arguments number for -neg, should be 0");
    }
    return std::make_shared<Negative>();
}