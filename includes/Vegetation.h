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
    explicit Vegetation(SpeciesEnum s = SpeciesEnum::NoSpecies, double b = 0)
        : species(s), biomass(b) {}

    [[nodiscard]] bool isEmpty() const { return species == SpeciesEnum::NoSpecies; }
    [[nodiscard]] SpeciesEnum getSpecies() const { return species; }
    [[nodiscard]] double getBiomass() const { return biomass; }

    void Iterate() {}
    void setSpecies(SpeciesEnum s) { species = s; biomass = 0.1; }
};


#endif //IMS_VEGETATION_H