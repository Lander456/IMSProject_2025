//
// Created by tadeas on 2025-12-01.
//

#include "../includes/Simulator.h"
#include "../includes/Vegetation.h"

void Simulator::seedFirstGeneration(const size_t numOfAcacias) {
    if (!acaciaCoords.empty()) {
        for (const auto& coord : acaciaCoords) {
            map_->at(coord.first, coord.second)->vegetation->setSpecies(SpeciesEnum::Acacia);
        }
    }
    std::uniform_int_distribution<size_t> distX(0, map_->getWidth() - 1);
    std::uniform_int_distribution<size_t> distY(0, map_->getHeight() - 1);
    for (size_t i = 0; i < numOfAcacias; i++) {
        bool attemptingToPlant = true;
        while (attemptingToPlant) {
            const size_t randX = distX(generator_);
            const size_t randY = distY(generator_);

            if (map_->at(randX, randY)->terrain.isHabitable() && map_->at(randX, randY)->terrain.getType() != TerrainTypesEnum::Field) {
                attemptingToPlant = false;
                map_->at(randX, randY)->vegetation->setSpecies(SpeciesEnum::Acacia);
                acaciaCoords.emplace_back(randX, randY);
            }
        }
    }
}

void Simulator::iterate(const ssize_t numOfIterations) const {
    std::cout << "Beggining iteration" << std::endl;
    for (size_t i = 0; i < numOfIterations; i++) {
        map_->iterate();
    }
    std::cout << "Iterated!" << std::endl;
}

void Simulator::runSimulation() const {
    if (outputWindow_->Construct(static_cast<int>(map_->getWidth()), static_cast<int>(map_->getHeight()), 4, 4)) {
        outputWindow_->Start();
    }
}

void Simulator::resetSim() {
    generationsSimulated_ = 0;

}

Simulator::Simulator(std::unique_ptr<Map> map, const ssize_t generationsToSim, const bool manualMode, const size_t numOfAcacias)
    : map_(std::move(map)), generationsToSim_(generationsToSim), generationsSimulated_(0), numOfAcacias_(numOfAcacias) {
    std::random_device rd;
    generator_ = std::mt19937(rd());
    outputWindow_ = std::make_unique<OutputWindow>();
    outputWindow_->init(map_.get(), this, manualMode);
    seedFirstGeneration(numOfAcacias);
}
