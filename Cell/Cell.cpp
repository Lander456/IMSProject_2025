//
// Created by tadeas on 2025-11-27.
//

#include "../includes/Config.h"
#include "../includes/Cell.h"


class Cell {
protected:
    Map& map_;
    int gridX_;
    int gridY_;

public:
    Terrain terrain;
    Soil soil;
    Vegetation vegetation;
    double shade;

    virtual void Iterate() { return; }
    virtual void Fertilise() { return; }
    virtual void OnRain() {return; }

    explicit Cell(Map& map, int x, int y, TerrainTypesEnum terainType) : 
        map_(map), gridX_(x), gridY_(y), terrain(terainType), soil(0.0,0.0), vegetation(), shade(0.0) {}

};

//shared logic for Dirt, Gravel and Field -> flooding, finding neighbor to nearest water
class HabitableCell : public Cell{
public:
        HabitableCell(Map& map, int x, int y, TerrainTypesEnum type) : Cell(map, x, y,type) {}

protected:
    Cell* floodDirectionCell_;

    void findFloodDirectionCell(){
        floodDirectionCell_ = map_.findFloodDirectionNeighbor(gridX_, gridY_);
    }

    void floodNitre(){

        if(soil.getMoisture() >= Config::floodTreshold){
            if(floodDirectionCell_ == nullptr) return;

            floodDirectionCell_->soil.addMoisture(soil.getMoisture() * Config::floodMoistureTransferedPercentage);
            floodDirectionCell_->soil.addNitrate(soil.getNitrate() * Config::floodNitreTransferedPercentage);
            soil.decayMoisture(1.0 - Config::floodMoistureTransferedPercentage);
            soil.decayNitre(1.0 - Config::floodNitreTransferedPercentage);
        }
    }
};



class DirtCell : public HabitableCell {
public:
    DirtCell(Map& map, int x, int y) : HabitableCell(map, x, y,TerrainTypesEnum::Dirt)
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
    GravelCell(Map& map, int x, int y) : HabitableCell(map, x, y, TerrainTypesEnum::Gravel)
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
    FieldCell(Map& map, int x, int y) : HabitableCell(map, x, y, TerrainTypesEnum::Field)
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
protected:
    std::vector<Cell*> cellsInRange;
    
public:
    WaterCell(Map& map, int x, int y) : Cell(map, x, y, TerrainTypesEnum::Water)
    {
        cellsInRange = map.getCellsInRadius(gridX_, gridY_, Config::waterMoisturizationRange);
    }
    
    //add moisture to neightbor cells
    void Iterate() override 
    { 
        for(int i = 0; i < cellsInRange.size(); i++){
            if(cellsInRange[i]->terrain.isHabitable()){
                cellsInRange[i]->soil.addMoisture(Config::waterMoisturizationAmmount);
            }
        }
    }
};

class RockCell : public Cell {
public:
    RockCell(Map& map, int x, int y) : Cell(map, x, y, TerrainTypesEnum::Rock)
    {

    }
};