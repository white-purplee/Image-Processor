#include "parser.h"

void InputFilter::Clear() {
    filter_name = "";
    filter_params.clear();
}

ParserResults Parse(int argc, char** argv) {
    if (argc == 1) {
        std::cerr << text::INFO;
        return ParserResults();
    }
    if (argc < 3) {
        throw ParserException("File paths missing");
    }
    ParserResults result;
    result.input_file = argv[1];
    result.output_file = argv[2];
    InputFilter current_filter;
    for (int index = 3; index < argc; ++index) {
        if (argv[index][0] == '-') {
            if (index > 3) {
                result.input_filters.push_back(current_filter);
            }
            current_filter.Clear();
            current_filter.filter_name = argv[index];
        } else {
            current_filter.filter_params.push_back(argv[index]);
        }
        if (index == argc - 1) {
            result.input_filters.push_back(current_filter);
            current_filter.Clear();
        }
    }
    return result;
}