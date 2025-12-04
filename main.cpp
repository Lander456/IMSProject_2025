
#define OLC_PGE_APPLICATION

#include "includes/olcPixelGameEngine.h"
#include "includes/ArgParser.h"
#include "includes/MapParser.h"
#include "includes/Simulator.h"

int main (int argc, char *argv[]) {

    auto options = ArgParser::parseArgs(argc, argv);

    if (options.verbose) {
        std::cout << "Parsing input file: " << options.input_file << std::endl;
    }

    auto mapParser = MapParser(options.input_file);

    if (options.verbose) {
        std::cout << "Parsed input" << std::endl;
    }
    std::cout << "HEHE" << std::endl;
    auto map = mapParser.parseMap();
    std::cout << "HAHA" << std::endl;
    auto simulator = Simulator(std::move(map), options.gens);

    simulator.runSimulation();
}
