//
// Created by tadeas on 2025-11-30.
//

#ifndef IMS_ARGPARSER_H
#define IMS_ARGPARSER_H

#include <iostream>

class ArgParser {

private:
    typedef struct Options {
        std::string input_file;
        bool verbose;
        bool manualStepping;
        size_t gens;
    } options_t;

    static void printHelp(char *argv[]);

public:
    static options_t parseArgs(int argc, char *argv[]);

};

#endif //IMS_ARGPARSER_H