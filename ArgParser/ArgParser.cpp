//
// Created by tadeas on 2025-11-30.
//

#include "../includes/ArgParser.h"

#include <getopt.h>

#include "../includes/Errnos.h"

static option long_options[] = {
    {"help", no_argument, nullptr, 'h'},
    {"verbose", no_argument, nullptr, 'v'},
    {"input_file", required_argument, nullptr, 'f'},
    {"generations_to_simulate", required_argument, nullptr, 'g'},
    {"manual_stepping", no_argument, nullptr, 'm'},
    {nullptr, 0, nullptr, 0}
};

void ArgParser::printHelp(char *argv[]) {
    std::cout << "Usage: " << argv[0] << " [--help -h] [--verbose -v] [--input_file -f]" << std::endl;
}

ArgParser::options_t ArgParser::parseArgs(const int argc, char *argv[]) {
    int opt;
    int option_index = 0;

    options_t options = {};

    while ((opt = getopt_long(argc, argv, "f:g:vhm", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'v':
                options.verbose = true;
                break;
            case 'f':
                options.input_file = optarg;
                break;
            case 'g':
                errno = 0;
                char* end;
                options.gens = std::strtol(optarg, &end, 10);

                if (errno == ERANGE || *end != '\0' || options.gens <= 0) {
                    std::cerr << "Invalid generations amount, if you want the simulation to go on indefinitely, do not input this arg, otherwise please input a number greater than 0" << std::endl;
                    exit(INVALID_ARGS);
                }
                break;
            case 'm':
                options.manualStepping = true;
                break;
            case '?':
                std::cerr << "Unknown option " << static_cast<char>(optopt) << std::endl;
                printHelp(argv);
                exit(INVALID_ARGS);
            case 'h':
            default:
                std::cout << "Usage: " << argv[0] << " [--help -h] [--verbose -v] [--input_file -f] [--manual_stepping -m]" << std::endl;
                exit(0);
        }
    }

    if (options.input_file.empty()) {
        std::cerr << "No input file given" << std::endl;
        printHelp(argv);
        exit(INVALID_ARGS);
    }

    return options;
}
