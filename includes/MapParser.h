//
// Created by tadeas on 2025-11-29.
//

#ifndef IMS_MAPPARSER_H
#define IMS_MAPPARSER_H

#include "Map.h"
#include <fstream>
#include <unordered_map>

class MapParser {
private:

    const std::unordered_map<char, TerrainTypesEnum> TerrainLegend = {
        {':', TerrainTypesEnum::Dirt},
        {'|', TerrainTypesEnum::Dirt},
        {'.', TerrainTypesEnum::Rock},
        {'~', TerrainTypesEnum::Water},
        {';', TerrainTypesEnum::Field}
    };

    const std::unordered_map<char, SpeciesEnum> SpeciesLegend = {
        {':', SpeciesEnum::Grass},
        {';', SpeciesEnum::None},
        {'.', SpeciesEnum::None},
        {'~', SpeciesEnum::None},
        {'|', SpeciesEnum::Trees}
    };

    std::string filename_;

    std::ifstream inputFile_;

    void openInput(const std::string&);

    std::vector<std::string> getLines();

public:

    explicit MapParser(std::string inputFileName);

    void parseMap();

};


#endif //IMS_MAPPARSER_H