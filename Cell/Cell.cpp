//
// Created by tadeas on 2025-11-27.
//

#include "../includes/Config.h"
#include "../includes/Cell.h"


void Cell::Iterate() {
    return;
}

void Cell::Fertilise() {
    return;
}

void Cell::OnRain() {
    return;
}

Cell::Cell(Map& map, int x, int y, TerrainTypesEnum terainType)
    : map_(map), gridX_(x), gridY_(y), terrain(terainType), soil(0.0,0.0), vegetation(), shade(0.0) {}

//shared logic for Dirt, Gravel and Field -> flooding, finding neighbor to nearest water
HabitableCell::HabitableCell(Map &map, int x, int y, TerrainTypesEnum type)
    : Cell(map, x, y, type), floodDirectionCell_() {}

void HabitableCell::findFloodDirectionCell() {
    floodDirectionCell_ = map_.findFloodDirectionNeighbor(gridX_, gridY_);
}

void HabitableCell::floodNitre() {

        if (soil.getMoisture() >= Config::floodTreshold) {
            if (floodDirectionCell_ == nullptr) {
                return;
            }

            floodDirectionCell_->soil.addMoisture(soil.getMoisture() * Config::floodMoistureTransferedPercentage);
            floodDirectionCell_->soil.addNitrate(soil.getNitrate() * Config::floodNitreTransferedPercentage);
            soil.decayMoisture(1.0 - Config::floodMoistureTransferedPercentage);
            soil.decayNitre(1.0 - Config::floodNitreTransferedPercentage);
        }
}

::DirtCell::DirtCell(Map &map, int x, int y)
    : HabitableCell(map, x, y, TerrainTypesEnum::Dirt){
    soil.addMoisture(Config::dirtMoisture);
    soil.addNitrate(Config::dirtNitre);
}

void DirtCell::Iterate() {
    floodNitre();
    vegetation.Iterate();
    soil.decayMoisture(Config::dirtMoistureDecayRate);
    soil.decayNitre(Config::dirtNitreDecayRate);
}

void ::DirtCell::OnRain() {
    soil.addMoisture(Config::rainAddedMoisture * Config::dirtOnRainMoistureCaptured);
}

GravelCell::GravelCell(Map &map, int x, int y)
    : HabitableCell(map, x, y, TerrainTypesEnum::Gravel){
    soil.addMoisture(Config::gravelMoisture);
    soil.addNitrate(Config::gravelNitre);
}

void GravelCell::Iterate() {
    floodNitre();
    vegetation.Iterate();
    soil.decayMoisture(Config::gravelMoistureDecayRate);
    soil.decayNitre(Config::gravelNitreDecayRate);
}

void GravelCell::OnRain() {
    soil.addMoisture(Config::rainAddedMoisture * Config::gravelOnRainMoistureCaptured);
}

FieldCell::FieldCell(Map &map, int x, int y)
    : HabitableCell(map, x, y, TerrainTypesEnum::Field){
    soil.addMoisture(Config::fieldMoisture);
    soil.addNitrate(Config::fieldNitre);
}

void FieldCell::Iterate() {
    floodNitre();
    soil.decayMoisture(Config::fieldMoistureDecayRate);
    soil.decayNitre(Config::fieldNitreDecayRate);
}

void FieldCell::OnRain() {
    soil.addMoisture(Config::rainAddedMoisture * Config::fieldOnRainMoistureCaptured);
}

void FieldCell::Fertilise() {
    soil.addNitrate(Config::fieldNitreFertilisedAmmount);
}

WaterCell::WaterCell(Map &map, int x, int y)
    : Cell(map, x, y, TerrainTypesEnum::Water) {
    cellsInRange_ = map.getCellsInRadius(gridX_, gridY_, Config::waterMoisturizationRange);
}

void WaterCell::Iterate() {
    for (int i = 0; i < cellsInRange_.size(); i++) {
        if (cellsInRange_[i]->terrain.isHabitable()) {
            cellsInRange_[i]->soil.addMoisture(Config::waterMoisturizationAmmount);
        }
    }
}

RockCell::RockCell(Map &map, int x, int y)
    : Cell(map, x, y, TerrainTypesEnum::Rock){}