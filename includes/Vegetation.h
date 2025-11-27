//
// Created by tadeas on 2025-11-27.
//

#ifndef IMS_VEGETATION_H
#define IMS_VEGETATION_H

#include "SpeciesEnum.h"


class Vegetation {
private:
    SpeciesEnum species;
    double biomass;

public:
    Vegetation(SpeciesEnum s = SpeciesEnum::None, double b = 0)
        : species(s), biomass(b) {}

    bool isEmpty() const { return species == SpeciesEnum::None; }
    SpeciesEnum getSpecies() const { return species; }
    double getBiomass() const { return biomass; }

    void grow (double amt) { biomass += amt; }
    void setSpecies(SpeciesEnum s) { species = s; biomass = 0.1; }
};


#endif //IMS_VEGETATION_H