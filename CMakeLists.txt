project(image_processor)

add_compile_options(-std=c++20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(
    image_processor
    image_processor.cpp
    bmp.cpp
    controller.cpp
    image.cpp
    parser.cpp
    filters/base_filter.cpp
    filters/crop.cpp
    filters/edge_detection.cpp
    filters/gray_scale.cpp
    filters/negative.cpp
    filters/sharpening.cpp
    filters/blur.cpp
    filters/light_distortion.cpp
    fabrics/crop_fabric.cpp
    fabrics/edge_detection_fabric.cpp
    fabrics/gray_scale_fabric.cpp
    fabrics/negative_fabric.cpp
    fabrics/sharpening_fabric.cpp
    fabrics/blur_fabric.cpp
    fabrics/light_distortion_fabric.cpp
)

add_catch(test image_processor.cpp)