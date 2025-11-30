
#include "includes/ArgParser.h"
#include "includes/MapParser.h"

int main (int argc, char *argv[]) {

    auto options = ArgParser::parseArgs(argc, argv);

    if (options.verbose) {
        std::cout << "Parsing input file: " << options.input_file << std::endl;
    }

    auto mapParser = MapParser(options.input_file);

    mapParser.parseMap();

}
