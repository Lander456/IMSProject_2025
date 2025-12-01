//
// Created by tadeas on 2025-12-01.
//

#ifndef IMS_SIMULATOR_H
#define IMS_SIMULATOR_H

#include <random>

#include "Map.h"


class Simulator {
private:
    size_t generationsToSim_;
    std::unique_ptr<Map> map_;
    std::mt19937 generator_;

public:
    explicit Simulator(std::unique_ptr<Map> map, size_t generationsToSim = -1);

    void seedFirstGeneration(size_t numOfAcacias);

    void runSimulation();
};


#endif //IMS_SIMULATOR_H