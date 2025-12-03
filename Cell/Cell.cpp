//
// Created by tadeas on 2025-11-27.
//

#include "../includes/Config.h"
#include "../includes/Cell.h"


/* == CELL == */
Cell::Cell(Map& map, int x, int y, TerrainTypesEnum terainType)
    : map_(map), gridX_(x), gridY_(y), terrain(terainType), soil(0.0,0.0), vegetation(std::make_unique<Vegetation>()), shade(0.0) {}

void Cell::Iterate(IterationPhase phase) {
    return;
}

void Cell::Fertilise() {
    return;
}

void Cell::OnRain() {
    return;
}

void Cell::SetUp(){
    return;
}

/* == HABITABLE CELL == */
//shared logic for Dirt, Gravel and Field -> flooding, finding neighbor to nearest water
HabitableCell::HabitableCell(Map &map, int x, int y, TerrainTypesEnum type)
    : Cell(map, x, y, type), floodDirectionCell_() {}


void HabitableCell::SetUp(){
    floodDirectionCell_ = map_.findFloodDirectionNeighbor(gridX_, gridY_);
    cellsInRange = map_.getCellsInRadius(gridX_, gridY_, 1);
}

void HabitableCell::flood() {

    if (soil.getMoisture() >= Config::floodTreshold) {
        if (floodDirectionCell_ == nullptr || floodDirectionCell_->terrain.getType() == TerrainTypesEnum::Rock) {
            return;
        }

        if(floodDirectionCell_->terrain.getType() != TerrainTypesEnum::Water){
            floodDirectionCell_->incomingSoilChanges.first += (soil.getMoisture() * Config::floodMoistureTransferedPercentage);
            floodDirectionCell_->incomingSoilChanges.second += (soil.getNitrate() * Config::floodNitreTransferedPercentage);
        }
        soil.decayMoisture(1.0 - Config::floodMoistureTransferedPercentage);
        soil.decayNitre(1.0 - Config::floodNitreTransferedPercentage);
    }
}

/* == DIRT CELL == */
DirtCell::DirtCell(Map &map, int x, int y)
    : HabitableCell(map, x, y, TerrainTypesEnum::Dirt){
    soil.addMoisture(Config::dirtMoisture);
    soil.addNitrate(Config::dirtNitre);
}

void DirtCell::Iterate(IterationPhase phase) {

    switch (phase)
    {
    case IterationPhase::Soil:
        flood();
        soil.decayMoisture(Config::dirtMoistureDecayRate);
        soil.decayNitre(Config::dirtNitreDecayRate);
        soil.addNitrate(Config::passiveNitreGain);

        //TODO - calculate shade
        break;
    case IterationPhase::Vegetation:
        vegetation->Iterate(this);
        break;
    }
    
    
}

void DirtCell::OnRain() {
    soil.addMoisture(Config::rainAddedMoisture * Config::dirtOnRainMoistureCaptured);
}

/* == GRAVEL CELL == */
GravelCell::GravelCell(Map &map, int x, int y)
    : HabitableCell(map, x, y, TerrainTypesEnum::Gravel){
    soil.addMoisture(Config::gravelMoisture);
    soil.addNitrate(Config::gravelNitre);
}

void GravelCell::Iterate(IterationPhase phase) {

    switch (phase)
    {
    case IterationPhase::Soil:
        flood();
        soil.decayMoisture(Config::gravelMoistureDecayRate);
        soil.decayNitre(Config::gravelNitreDecayRate);
        soil.addNitrate(Config::passiveNitreGain);
        break;
    case IterationPhase::Vegetation:
        vegetation->Iterate(this);
        break;
    }
}

void GravelCell::OnRain() {
    soil.addMoisture(Config::rainAddedMoisture * Config::gravelOnRainMoistureCaptured);
}

/* == FIELD CELL == */
FieldCell::FieldCell(Map &map, int x, int y)
    : HabitableCell(map, x, y, TerrainTypesEnum::Field){
    soil.addMoisture(Config::fieldMoisture);
    soil.addNitrate(Config::fieldNitre);
}

void FieldCell::Iterate(IterationPhase phase) {
    switch (phase)
    {
    case IterationPhase::Soil:
        flood();
        soil.decayMoisture(Config::fieldMoistureDecayRate);
        soil.decayNitre(Config::fieldNitreDecayRate);
        soil.addNitrate(Config::passiveNitreGain);
        break;
    case IterationPhase::Vegetation:
        break;
    }
}

void FieldCell::OnRain() {
    soil.addMoisture(Config::rainAddedMoisture * Config::fieldOnRainMoistureCaptured);
}

void FieldCell::Fertilise() {
    soil.addNitrate(Config::fieldNitreFertilisedAmmount);
}

/* == WATER CELL == */
WaterCell::WaterCell(Map &map, int x, int y)
    : Cell(map, x, y, TerrainTypesEnum::Water) {}

void WaterCell::SetUp(){
    cellsInRange_ = map_.getCellsInRadius(gridX_, gridY_, Config::waterMoisturizationRange);
}

void WaterCell::Iterate(IterationPhase phase) {

    for(Cell* c : cellsInRange_){
        if(!c) continue;
        if(c->terrain.isHabitable()){
            c->soil.addMoisture(Config::waterMoisturizationAmmount);
        }
    }
}

/* == ROCK CELL == */
RockCell::RockCell(Map &map, int x, int y)
    : Cell(map, x, y, TerrainTypesEnum::Rock){}