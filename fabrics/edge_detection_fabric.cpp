#include "edge_detection_fabric.h"

#include "../filters/edge_detection.h"

std::shared_ptr<BaseFilter> EdgeDetectionFabric::Create(const std::vector<std::string>& input_params) {
    if (input_params.size() != 1) {
        throw FilterException("Wrong arguments number for -edge, should be 1");
    }
    double threshold = NAN;
    try {
        threshold = std::stod(input_params[0]);
    } catch (const std::exception& ex) {
        throw FilterException("Wrong argument type for -edge, should be double");
    }
    return std::make_shared<EdgeDetection>(threshold);
}