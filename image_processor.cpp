#include "bmp.h"
#include "controller.h"
#include "exception.h"
#include "image.h"
#include "parser.h"

#include <iostream>

int main(int argc, char** argv) {
    ParserResults parsed;
    try {
        parsed = Parse(argc, argv);
        if (argc == 1) {
            return 0;
        }
    } catch (const std::exception& ex) {
        std::cerr << "While parsing an error occurred: " << ex.what() << '\n';
        return 1;
    }
    Image image;
    try {
        image = BMPRead(parsed.input_file);
    } catch (const std::exception& ex) {
        std::cerr << "While reading image an error occurred: " << ex.what() << '\n';
        return 1;
    }
    std::vector<std::shared_ptr<BaseFilter>> filters;
    try {
        filters = CreateFilters(parsed.input_filters);
    } catch (const std::exception& ex) {
        std::cerr << "While creating filters an error occurred: " << ex.what() << '\n';
        return 1;
    }
    try {
        ApplyFilters(filters, image);
    } catch (const std::exception& ex) {
        std::cerr << "While applying filters an error occurred: " << ex.what() << '\n';
        return 1;
    }
    try {
        BMPWrite(image, parsed.output_file);
    } catch (const std::exception& ex) {
        std::cerr << "While writing the result an error occurred: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}
