//
// Created by tadeas on 2025-11-27.
//

#include "../includes/SpeciesRegistry.h"
#include "../includes/Vegetation.h"
#include "../includes/Config.h"
#include "../includes/SpeciesEnum.h"
#include <cstdlib>


void Vegetation::Iterate(HabitableCell* cell){
    if(species == SpeciesEnum::NoSpecies) return;

    
    const SpeciesInfo& info = SpeciesRegistry::getSpeciesInfo(species);
    double growFactor = 1.0;
    
    //check for too much shade 
    auto shadeFactor = info.shadeTolerance - cell->shade/Config::maxSoilShade;
    if( shadeFactor < 0){
        growFactor += shadeFactor * Config::shadeWitherFactor;
    }
    //check for valid moisture
    auto cellMoist = cell->soil.getMoisture();
    if(cellMoist < info.moistureMinTolerance){ //not enough water
        growFactor += (cellMoist - info.moistureMinTolerance) * Config::moistureWitherFactor;
    }
    else if(cellMoist > info.moistureMaxTolerance){ //too much water
        growFactor += (info.moistureMaxTolerance - cellMoist) * Config::moistureWitherFactor;
    }

    //check for valid nitrate
    auto cellNitrate = cell->soil.getNitrate();
    if(cellNitrate < info.nitreMinTolerance){ //not enough nitre
        growFactor += (cellNitrate - info.nitreMinTolerance) * Config::nitreWitherFactor;
    }
    else if(cellNitrate > info.nitreMaxTolerance){ //too much nitre
        growFactor += (info.nitreMaxTolerance - cellNitrate) * Config::nitreWitherFactor;
    }
    else if(growFactor > 0){ //ideal ammount of nitrate and not withering from shade or water
        growFactor *= info.nitrogenBonus;
    }

    //produce nitre if acacia
    if(species == SpeciesEnum::Acacia)
    {
        //add nitre for self and neighbor cells
        for(auto c : cell->cellsInRange){
            if(!c) continue;
            if(c->terrain.isHabitable()){
                c->soil.addNitrate(biomass/info.maxHeight * Config::extraNitrateFactor);
            }
        }
    }
    

    //grow or shrink
    double growAmmount = Config::staticGrowRate * info.growthRate * growFactor;
    if(biomass+growAmmount > info.maxHeight){ //max grow
        auto realGrowth = info.maxHeight - biomass;
        biomass = info.maxHeight;
        //update shade
        for(auto c : cell->cellsInRange){
            if(!c || c==cell) continue; //skip if null or current cell
            c->shade += ((realGrowth/info.maxHeight)*info.shadeCreated)/4; //1/4 becouse effects 4 neighbor cells
        }
    }
    else if(biomass+growAmmount <= 0){ //plant died
        auto realWither = -biomass;
        biomass = 0;
        species = SpeciesEnum::NoSpecies;
        //update shade
        for(auto c : cell->cellsInRange){
            if(!c || c==cell) continue; //skip if null or current cell
            c->shade += ((realWither/info.maxHeight)*info.shadeCreated)/4;
        }
        return;
    }
    else{ //normal grow
        biomass += growAmmount;
        //update shade
        for(auto c : cell->cellsInRange){
            if(!c || c==cell) continue; //skip if null or current cell
            c->shade += ((growAmmount/info.maxHeight)*info.shadeCreated)/4; 
        }
    }

    //try to spread on free cells if biomass big enough
    if(growFactor > 0 && biomass >= info.minimalSpreadBiomass){
        for(auto c : cell->cellsInRange){
            if(!c) continue;
            if(c->terrain.isHabitable() && c->vegetation->isEmpty()){ 
                double roll = static_cast<double>(rand() / static_cast<double>(RAND_MAX));
                if(roll <= Config::defaultSpreadChance * info.spreadModifier){ //succes on spread chance
                    c->vegetation->setSpecies(species);
                }
            }
        }
    }
}