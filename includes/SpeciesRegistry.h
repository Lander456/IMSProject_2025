//
// Created by tadeas on 2025-11-27.
//

#ifndef IMS_SPECIESREGISTRY_H
#define IMS_SPECIESREGISTRY_H

#include <unordered_map>

#include "SpeciesEnum.h"
#include "SpeciesInfo.h"


class SpeciesRegistry {
private:
    static std::unordered_map<SpeciesEnum, SpeciesInfo> speciesMap;

public:
    static void initializeSpeciesRegistry();
    static const SpeciesInfo& getSpeciesInfo(SpeciesEnum species);
};


#endif //IMS_SPECIESREGISTRY_H