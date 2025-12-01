
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

    auto map = mapParser.parseMap();

    std::ofstream outputFile("log.log");

    for (size_t y = 0; y < map->getHeight(); y++) {
        for (size_t x = 0; x < map->getWidth(); x++) {
            outputFile << map->at(x, y)->terrain.getTerrainChar();
        }
        outputFile << std::endl;
    }

    outputFile.close();

    auto simulator = Simulator(std::move(map), options.gens);

}
