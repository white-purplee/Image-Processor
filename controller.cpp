#include "controller.h"

extern const std::unordered_map<std::string, std::shared_ptr<BaseFabric>> FABRICS = {
    {"-crop", std::make_shared<CropFabric>()},           {"-gs", std::make_shared<GrayScaleFabric>()},
    {"-neg", std::make_shared<NegativeFabric>()},        {"-sharp", std::make_shared<SharpeningFabric>()},
    {"-edge", std::make_shared<EdgeDetectionFabric>()},  {"-blur", std::make_shared<BlurFabric>()},
    {"-dist", std::make_shared<LightDistortionFabric>()}};

std::vector<std::shared_ptr<BaseFilter>> CreateFilters(const std::vector<InputFilter>& input_filters) {
    std::vector<std::shared_ptr<BaseFilter>> created_filters;
    for (const auto& input_filter : input_filters) {
        auto fabric = FABRICS.find(input_filter.filter_name);
        if (fabric == FABRICS.end()) {
            throw ControllerException("Wrong filter name: " + input_filter.filter_name);
        }
        created_filters.push_back(fabric->second->Create(input_filter.filter_params));
    }
    return created_filters;
}

void ApplyFilters(const std::vector<std::shared_ptr<BaseFilter>>& filters, Image& image) {
    for (const auto& filter : filters) {
        filter->Apply(image);
    }
}