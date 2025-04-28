#pragma once

#include "base_fabric.h"

class NegativeFabric : public BaseFabric {
public:
    std::shared_ptr<BaseFilter> Create(const std::vector<std::string>& input_params) override;
};