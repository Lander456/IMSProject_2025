//
// Created by tadeas on 2025-11-27.
//

#include "../includes/Config.h"
#include "../includes/Cell.h"

//shared logic for Dirt, Gravel and Field -> flooding, finding neighbor to nearest water
class HabitableCell : public Cell{
protected:
    Cell* floodDirectionCell;

    Cell* findFloodDirectionCell(){
        
        /*TODO*/
        return nullptr; 
    }

    void floodNitre(){

        if(soil.getMoisture() >= Config::floodTreshold){
            if(floodDirectionCell == nullptr) return;

            floodDirectionCell->soil.addMoisture(soil.getMoisture() * Config::floodMoistureTransferedPercentage);
            floodDirectionCell->soil.addNitrate(soil.getNitrate() * Config::floodNitreTransferedPercentage);
            soil.decayMoisture(1.0 - Config::floodMoistureTransferedPercentage);
            soil.decayNitre(1.0 - Config::floodNitreTransferedPercentage);
        }
    }

public:
    HabitableCell(Map& map, TerrainTypesEnum type) : Cell(map, type){}
    
};



class DirtCell : public HabitableCell {
public:
    DirtCell(Map& map) : HabitableCell(map, TerrainTypesEnum::Dirt)
    {
        soil.addMoisture(Config::dirtMoisture);
        soil.addNitrate(Config::dirtNitre);
    }
    
    void Iterate() override {

        floodNitre();
        vegetation.Iterate();
        soil.decayMoisture(Config::dirtMoistureDecayRate);
        soil.decayNitre(Config::dirtNitreDecayRate);
    }
    
    void OnRain() override {
        soil.addMoisture(Config::rainAddedMoisture * Config::dirtOnRainMoistureCaptured);
    }
};


class GravelCell : public HabitableCell {
public:
    GravelCell(Map& map) : HabitableCell(map, TerrainTypesEnum::Gravel)
    {
        soil.addMoisture(Config::gravelMoisture);
        soil.addNitrate(Config::gravelNitre);
    }
    
    void Iterate() override {
        floodNitre();
        vegetation.Iterate();
        soil.decayMoisture(Config::gravelMoistureDecayRate);
        soil.decayNitre(Config::gravelNitreDecayRate);
    }
    
    void OnRain() override {
        soil.addMoisture(Config::rainAddedMoisture * Config::gravelOnRainMoistureCaptured);
    }
};

class FieldCell : public HabitableCell {
public:
    FieldCell(Map& map) : HabitableCell(map, TerrainTypesEnum::Field)
    {
        soil.addMoisture(Config::fieldMoisture);
        soil.addNitrate(Config::fieldNitre); 
    }
    
    void Iterate() override {
        floodNitre();
        soil.decayMoisture(Config::fieldMoistureDecayRate);
        soil.decayNitre(Config::fieldNitreDecayRate);
    }
    
    void OnRain() override {
        soil.addMoisture(Config::rainAddedMoisture * Config::fieldOnRainMoistureCaptured);
    }

    void Fertilise() override {
        soil.addNitrate(Config::fieldNitreFertilisedAmmount);
    }
};

class WaterCell : public Cell {
    
    
public:
    WaterCell(Map& map) : Cell(map, TerrainTypesEnum::Water)
    {
        
    }
    
    //add moisture to neightbor cells
    void Iterate() override 
    { 
        /*TODO*/
    }
    
};

class RockCell : public Cell {
public:
    RockCell(Map& map) : Cell(map, TerrainTypesEnum::Rock)
    {

    }
};