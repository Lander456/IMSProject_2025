//
// Created by tadeas on 2025-11-29.
//



#include <utility>
#include <iostream>
#include <random>

#include "../includes/MapParser.h"

void MapParser::openInput(const std::string&) {

    inputFile_ = std::ifstream(filename_, std::ios::in);

    if (!inputFile_.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        exit(1);
    }

}

MapParser::MapParser(std::string inputFileName) : filename_(std::move(inputFileName)) {

    openInput(filename_);

    const auto lines = getLines();

    size_t height = lines.size();
    size_t width = lines[0].size();

    auto map = Map(width, height);

    parseMap(map, lines);

}

void MapParser::parseMap(Map map, std::vector<std::string> lines) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (size_t y = 0; y < lines.size(); y++) {
        std::string& line = lines[y];

        for (size_t x = 0; x < map.getWidth(); x++) {

            auto cell = map.at(x, y);

            auto terrain = Terrain(TerrainLegend.at(line[x]));
            auto vegetation = Vegetation(SpeciesLegend.at(line[x]), dist(gen));

            cell.setTerrain(terrain);
            cell.setVegetation(vegetation);

        }
    }

}

std::vector<std::string> MapParser::getLines() {

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(inputFile_, line)) {
        lines.push_back(line);
    }

    return lines;
}
