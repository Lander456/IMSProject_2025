
#define OLC_PGE_APPLICATION

#include "includes/olcPixelGameEngine.h"
#include "includes/ArgParser.h"
#include "includes/MapParser.h"
#include "includes/Simulator.h"

int main (int argc, char *argv[]) {

    const auto options = ArgParser::parseArgs(argc, argv);
    auto mapParser = MapParser(options.input_file);
    auto map = mapParser.parseMap();
    map->setFertilization(options.fertilization);
    const auto simulator = Simulator(std::move(map), options.gens, options.manualStepping, options.numOfAcacias);

    simulator.runSimulation();
}
