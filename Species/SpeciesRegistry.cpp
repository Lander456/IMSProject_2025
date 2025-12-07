

#include "../includes/SpeciesRegistry.h"

#include <iostream>
#include <ostream>

#include "../includes/Config.h"
#include <stdexcept>

std::unordered_map<SpeciesEnum, SpeciesInfo> SpeciesRegistry::speciesMap;

void SpeciesRegistry::initializeSpeciesRegistry(){
    speciesMap[SpeciesEnum::Acacia] = {
        Config::acaciaGrowthRate,
        Config::acaciaNitrogenBonus,
        Config::acaciaShadeTolerance,
        Config::acaciaShadeCreated,
        Config::acaciaSpreadModifier,
        Config::acaciaMaxHeight,
        Config::acaciaNitreMaxTolerance,
        Config::acaciaSpreadBiomass
    };

    speciesMap[SpeciesEnum::Shrub] = {
        Config::shrubGrowthRate,
        Config::shrubNitrogenBonus,
        Config::shrubShadeTolerance,
        Config::shrubShadeCreated,
        Config::shrubSpreadModifier,
        Config::shrubMaxHeight,
        Config::shrubNitreMaxTolerance,
        Config::shrubSpreadBiomass
    };

    speciesMap[SpeciesEnum::Grass] = {
        Config::grassGrowthRate,
        Config::grassNitrogenBonus,
        Config::grassShadeTolerance,
        Config::grassShadeCreated,
        Config::grassSpreadModifier,
        Config::grassMaxHeight,
        Config::grassNitreMaxTolerance,
        Config::grassSpreadBiomass
    };

    speciesMap[SpeciesEnum::Trees] = {
        Config::treeGrowthRate,
        Config::treeNitrogenBonus,
        Config::treeShadeTolerance,
        Config::treeShadeCreated,
        Config::treeSpreadModifier,
        Config::treeMaxHeight,
        Config::treeNitreMaxTolerance,
        Config::treeSpreadBiomass
    };

    speciesMap[SpeciesEnum::NoSpecies] = {};

    //std::cerr << "Registry initialized" << std::endl;
}

const SpeciesInfo& SpeciesRegistry::getSpeciesInfo(SpeciesEnum species){
    auto registryRecord = speciesMap.find(species);
    if (registryRecord == speciesMap.end()) {
        throw std::runtime_error("Species not in registry");
    }
    return registryRecord->second;
}