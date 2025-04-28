#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "exception.h"

namespace text {
const std::string INFO =
    "Program interaction protocol:\n"
    "1. The first word in the input is the name of the executable file.\n"
    "2. The path to your input file should be in the format: C:/Users/Username/Downloads/image.bmp\n"
    "3. The path to the output file should follow the same format as the input file.\n"
    "\n"
    "Next comes the filter description. Each filter should be specified in the format:\n"
    "  -{filter_name} {arg1} {arg2} ...\n"
    "\n"
    "Available filters and examples:\n"
    "\n"
    "-gs                  Converts the image to grayscale.\n"
    "                     Example: -gs\n"
    "\n"
    "-crop height width   Takes two arguments: height and width, and crops the image accordingly.\n"
    "                     Height and width should not be greater than the original image size,\n"
    "                     otherwise the filter won't change the image.\n"
    "                     Example: -crop 800 600\n"
    "\n"
    "-sharp               Increases sharpness.\n"
    "                     Example: -sharp\n"
    "\n"
    "-edge threshold      Takes one argument and highlights only the edges of objects in the image.\n"
    "                     threshold - should belong to the interval from 0.0 to 1.0.\n"
    "                     Example: -edge 0.5\n"
    "\n"
    "-blur sigma          Takes one argument and applies a blur effect.\n"
    "                     sigma - should not be too big, otherwise the filter might work long.\n"
    "                     Example: -blur 5\n"
    "\n"
    "-dist x y strength   Takes coordinates and strength and circles the image around those coordinates.\n"
    "                     x y - should be double numbers from 0.0 to 1.0.\n"
    "                     strength - can be any positive number, but makes sense only if not greater than 10.\n"
    "                     Example: -dist 0.5 0.5 1\n"
    "\n"
    "Example of multiple filters applied together:\n"
    "./image_processor input.bmp output.bmp -gs -crop 500 400 -sharp -blur 1.5\n";
}  // namespace text

struct InputFilter {
    std::string filter_name;
    std::vector<std::string> filter_params;
    void Clear();
};

struct ParserResults {
    std::string input_file;
    std::string output_file;
    std::vector<InputFilter> input_filters;
};

ParserResults Parse(int argc, char** argv);