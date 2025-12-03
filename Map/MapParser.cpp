//
// Created by tadeas on 2025-11-29.
//

#include <utility>
#include <iostream>
#include <random>

#include "../includes/MapParser.h"
#include "../includes/Cell.h"
#include "../includes/Errnos.h"
#include "../includes/Map.h"

void MapParser::openInput(const std::string&) {

    inputFile_ = std::ifstream(filename_, std::ios::in);

    if (!inputFile_.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        exit(INVALID_INPUT_FILE);
    }

}

MapParser::MapParser(std::string inputFileName) : filename_(std::move(inputFileName)) {
    openInput(filename_);
}

std::unique_ptr<Map> MapParser::parseMap() {

    auto lines = getLines();

    const size_t height = lines.size();
    const size_t width = lines[0].size();

    auto map = std::make_unique<Map>(width, height);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution dist(0.0f, 1.0f);

    for (int y = 0; y < lines.size(); y++) {
        std::string& line = lines[y];

        for (int x = 0; x < map->getWidth(); x++) {

            auto terrain = Terrain(TerrainLegend.at(line[x]));
            const auto vegetation = Vegetation(SpeciesLegend.at(line[x]), dist(gen));

            switch (terrain.getType()) {
                case TerrainTypesEnum::Dirt:
                    map->at(x, y) = std::make_unique<DirtCell>(*map, x, y);
                    break;
                case TerrainTypesEnum::Water:
                    map->at(x, y) = std::make_unique<WaterCell>(*map, x, y);
                    break;
                case TerrainTypesEnum::Rock:
                    map->at(x, y) = std::make_unique<RockCell>(*map, x, y);
                    break;
                case TerrainTypesEnum::Field:
                    map->at(x, y) = std::make_unique<FieldCell>(*map, x, y);
                    break;
                case TerrainTypesEnum::Gravel:
                    map->at(x, y) = std::make_unique<GravelCell>(*map, x, y);
                    break;
            }

            map->at(x, y)->vegetation = std::make_unique<Vegetation>(vegetation);

        }
    }

    return map;

}

std::vector<std::string> MapParser::getLines() {

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(inputFile_, line)) {
        lines.push_back(line);
    }

    return lines;
}
