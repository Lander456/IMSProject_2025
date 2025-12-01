//
// Created by tadeas on 2025-11-30.
//

#include "../includes/ArgParser.h"

#include <getopt.h>

static option long_options[] = {
    {"help", no_argument, nullptr, 'h'},
    {"verbose", no_argument, nullptr, 'v'},
    {"input_file", required_argument, nullptr, 'f'},
    {nullptr, 0, nullptr, 0}
};

void ArgParser::printHelp(char *argv[]) {
    std::cout << "Usage: " << argv[0] << " [--help -h] [--verbose -v] [--input_file -f]" << std::endl;
}

ArgParser::options_t ArgParser::parseArgs(const int argc, char *argv[]) {
    int opt;
    int option_index = 0;

    options_t options = {};

    while ((opt = getopt_long(argc, argv, "f:vh", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'v':
                options.verbose = true;
                break;
            case 'f':
                options.input_file = optarg;
                break;
            case '?':
                std::cerr << "Unknown option " << std::endl;
                printHelp(argv);
                exit(1);
            case 'h':
            default:
                std::cout << "Usage: " << argv[0] << " [--help -h] [--verbose -v] [--input_file -f]" << std::endl;
                exit(0);
        }
    }

    if (options.input_file.empty()) {
        std::cerr << "No input file given" << std::endl;
        printHelp(argv);
        exit(1);
    }

    return options;
}
