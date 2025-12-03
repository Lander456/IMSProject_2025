//
// Created by tadeas on 2025-12-01.
//

#include "../includes/Simulator.h"
#include "../includes/Vegetation.h"

void Simulator::seedFirstGeneration(const size_t numOfAcacias) {
    std::uniform_int_distribution<size_t> distX(0, map_->getWidth() - 1);
    std::uniform_int_distribution<size_t> distY(0, map_->getHeight() - 1);
    for (size_t i = 0; i < numOfAcacias; i++) {
        bool attemptingToPlant = true;
        while (attemptingToPlant) {
            const size_t randX = distX(generator_);
            const size_t randY = distY(generator_);

            if (map_->at(randX, randY)->terrain.isHabitable()) {
                attemptingToPlant = false;
                map_->at(randX, randY).get()->vegetation->setSpecies(SpeciesEnum::Acacia);
            }
        }
    }
}

void Simulator::runSimulation() {
    if (generationsToSim_ < 0) {
        while (true) {
            map_->iterate();
        }
    }
    for (size_t gen = 0; gen < generationsToSim_; gen++) {
        map_->iterate();
    }
}

Simulator::Simulator(std::unique_ptr<Map> map, const size_t generationsToSim)
    : generationsToSim_(generationsToSim), map_(std::move(map)) {
    std::random_device rd;
    generator_ = std::mt19937(rd());
}
