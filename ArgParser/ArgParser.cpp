//
// Created by tadeas on 2025-11-30.
//

#include "../includes/ArgParser.h"
#include "../includes/Errnos.h"

#include <getopt.h>

static option long_options[] = {
    {"help", no_argument, nullptr, 'h'},
    {"input_file", required_argument, nullptr, 'f'},
    {"generations_to_simulate", required_argument, nullptr, 'g'},
    {"manual_stepping", no_argument, nullptr, 'm'},
    {"number_of_acacias", required_argument, nullptr, 'a'},
    {"no_fertilize", no_argument, nullptr, 1},
    {nullptr, 0, nullptr, 0}
};

void ArgParser::printHelp(char *argv[]) {
    std::cout << "Usage: " << argv[0] << " [--help -h] [--verbose -v] [--input_file -f] [--manual_stepping -m] [--number_of_acacias -a] [--generations_to_simulate -g]" << std::endl;
    std::cout << "While the program is running, if manual stepping is enabled, you may proceed by 1 generation by pressing spacebar, while in this mode, you may choose how many generation to progres by by pressing 1 - 4 on your keyboard. When running in automatic mode you may increase the amount of generations undertaken in each iteration by pressing F up to 10 generations per iteration or slow it down by pressing S down to 1 generation per iteration. While the simulation is running, you may press N to view nitrogen concentrations per tile or M to view the moisture in each tile, by pressing V you may return to the vegetation map mode." << std::endl;
}

ArgParser::options_t ArgParser::parseArgs(const int argc, char *argv[]) {
    int opt;
    int option_index = 0;

    options_t options = {};

    while ((opt = getopt_long(argc, argv, "f:g:a:hm", long_options, &option_index)) != -1) {
        char* end;
        switch (opt) {
            case 'f':
                options.input_file = optarg;
                break;
            case 'g':
                errno = 0;
                options.gens = std::strtol(optarg, &end, 10);

                if (errno == ERANGE || *end != '\0' || options.gens <= 0) {
                    std::cerr << "Invalid generations amount, if you want the simulation to go on indefinitely, do not input this arg, otherwise please input a number greater than 0" << std::endl;
                    exit(INVALID_ARGS);
                }
                break;
            case 'm':
                options.manualStepping = true;
                break;
            case 'a':
                errno = 0;
                options.numOfAcacias = std::strtol(optarg, &end, 10);

                if (errno == ERANGE || *end != '\0' || options.numOfAcacias <= 0) {
                    std::cerr << "Invalid number of acacias given, if you do not input this argument, the default will be 3, otherwise please input a number greater than 0" << std::endl;
                    exit(INVALID_ARGS);
                }
                break;
            case 1:
                options.fertilization = false;
                break;
            case '?':
                std::cerr << "Unknown option " << static_cast<char>(optopt) << std::endl;
                printHelp(argv);
                exit(INVALID_ARGS);
            case 'h':
            default:
                printHelp(argv);
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
