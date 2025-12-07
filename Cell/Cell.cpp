//
// Created by tadeas on 2025-11-27.
//

#include "../includes/Config.h"
#include "../includes/Cell.h"
#include <iostream>


/* == CELL == */
Cell::Cell(Map& map, int x, int y, TerrainTypesEnum terainType)
    : map_(map), gridX_(x), gridY_(y), terrain(terainType), soil(0.0,0.0), vegetation(std::make_unique<Vegetation>()), shade(0.0) {}

void Cell::Iterate(IterationPhase phase) {
    return;
}

void Cell::Fertilise() {
    return;
}

void Cell::OnRain(double ammountRained) {
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

void HabitableCell::CheckForFlooding() {
    return;
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

    case IterationPhase::Flood:
        CheckForFlooding();
        break;    
    case IterationPhase::Soil:
        
        //update moisture
        soil.decayMoisture(Config::dirtMoistureDecayRate);
        soil.addMoisture(Config::passiveMoistureGain);
        //update nitre
        soil.decayNitre(Config::dirtNitreDecayRate);
        soil.addNitrate(Config::passiveNitreGain);

        break;
    case IterationPhase::Vegetation:
        vegetation->Iterate(this);
        break;
    }
    
    
}

void DirtCell::OnRain(double ammountRained) {
    soil.addMoisture(ammountRained * Config::dirtOnRainMoistureCaptured);
}

void DirtCell::CheckForFlooding(){

    if (soil.getMoisture() >= Config::dirtFC) {
        
        if (floodDirectionCell_ == nullptr || floodDirectionCell_->terrain.getType() == TerrainTypesEnum::Rock) {
            return;
        }

        double moistureFlooded = soil.getMoisture() - Config::dirtFC;
        double floodedPercentage = moistureFlooded / soil.getMoisture();
        double nitreFlooded = soil.getNitrate() * floodedPercentage * Config::nitrePercentageOnFlood;

        if(floodDirectionCell_->terrain.getType() != TerrainTypesEnum::Water){
            floodDirectionCell_->incomingSoilChanges.first += (moistureFlooded);
            floodDirectionCell_->incomingSoilChanges.second += (nitreFlooded);
        }
        soil.decayMoisture(1.0 - floodedPercentage);
        soil.decayNitre(1.0 - floodedPercentage * Config::nitrePercentageOnFlood);
    }
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
    case IterationPhase::Flood:
        CheckForFlooding();
        break;    
    case IterationPhase::Soil:
        //update moisture
        soil.decayMoisture(Config::gravelMoistureDecayRate);
        soil.addMoisture(Config::passiveMoistureGain);
        //update nitre
        soil.decayNitre(Config::gravelNitreDecayRate);
        soil.addNitrate(Config::passiveNitreGain);

        break;
    case IterationPhase::Vegetation:
        vegetation->Iterate(this);
        break;
    }
}

void GravelCell::OnRain(double ammountRained) {
    soil.addMoisture(ammountRained * Config::gravelOnRainMoistureCaptured);
}

void GravelCell::CheckForFlooding(){

    if (soil.getMoisture() >= Config::gravelFC) {
        
        if (floodDirectionCell_ == nullptr || floodDirectionCell_->terrain.getType() == TerrainTypesEnum::Rock) {
            return;
        }

        double moistureFlooded = soil.getMoisture() - Config::gravelFC;
        double floodedPercentage = moistureFlooded / soil.getMoisture();
        double nitreFlooded = soil.getNitrate() * floodedPercentage * Config::nitrePercentageOnFlood;

        if(floodDirectionCell_->terrain.getType() != TerrainTypesEnum::Water){
            floodDirectionCell_->incomingSoilChanges.first += (moistureFlooded);
            floodDirectionCell_->incomingSoilChanges.second += (nitreFlooded);
        }
        soil.decayMoisture(1.0 - floodedPercentage);
        soil.decayNitre(1.0 - floodedPercentage * Config::nitrePercentageOnFlood);
    }
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
    case IterationPhase::Flood:
        CheckForFlooding();
        break;    
    case IterationPhase::Soil:
        //update moisture
        soil.decayMoisture(Config::fieldMoistureDecayRate);
        soil.addMoisture(Config::passiveMoistureGain);
        //update nitre
        soil.decayNitre(Config::fieldNitreDecayRate);
        soil.addNitrate(Config::passiveNitreGain);

        break;
    case IterationPhase::Vegetation:
        vegetation->Iterate(this);
        break;
    }
}

void FieldCell::OnRain(double ammountRained) {
    soil.addMoisture(ammountRained * Config::fieldOnRainMoistureCaptured);
}

void FieldCell::CheckForFlooding(){

    if (soil.getMoisture() >= Config::fieldFC) {
        
        if (floodDirectionCell_ == nullptr || floodDirectionCell_->terrain.getType() == TerrainTypesEnum::Rock) {
            return;
        }

        double moistureFlooded = soil.getMoisture() - Config::fieldFC;
        double floodedPercentage = moistureFlooded / soil.getMoisture();
        double nitreFlooded = soil.getNitrate() * floodedPercentage * Config::nitrePercentageOnFlood;

        if(floodDirectionCell_->terrain.getType() != TerrainTypesEnum::Water){
            floodDirectionCell_->incomingSoilChanges.first += (moistureFlooded);
            floodDirectionCell_->incomingSoilChanges.second += (nitreFlooded);
        }
        soil.decayMoisture(1.0 - floodedPercentage);
        soil.decayNitre(1.0 - (floodedPercentage* Config::nitrePercentageOnFlood));
    }
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

    for(const auto& c : cellsInRange_){
        if(!c) continue;
        if(c->terrain.isHabitable()){
            c->soil.addMoisture(Config::waterMoisturizationAmmount);
        }
    }
}

/* == ROCK CELL == */
RockCell::RockCell(Map &map, int x, int y)
    : Cell(map, x, y, TerrainTypesEnum::Rock){}