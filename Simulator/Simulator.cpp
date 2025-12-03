//
// Created by tadeas on 2025-12-01.
//

#include "../includes/Simulator.h"

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
                map_->at(randX, randY)->vegetation = Vegetation(SpeciesEnum::Acacia);
            }
        }
    }
}

void Simulator::iterate(const size_t numOfIterations) const {
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

Simulator::Simulator(std::unique_ptr<Map> map, const size_t generationsToSim)
    : generationsToSim_(generationsToSim), map_(std::move(map)) {
    std::random_device rd;
    generator_ = std::mt19937(rd());
    outputWindow_ = std::make_unique<OutputWindow>();
    outputWindow_->init(map_.get(), this);
}
