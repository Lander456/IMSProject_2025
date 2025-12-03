//
// Created by tadeas on 2025-12-01.
//

#ifndef IMS_SIMULATOR_H
#define IMS_SIMULATOR_H

#include <random>

#include "Map.h"
#include "OutputWindow.h"

class OutputWindow;

class Simulator {
private:
    size_t generationsToSim_;
    std::unique_ptr<Map> map_;
    std::mt19937 generator_;
    std::unique_ptr<OutputWindow> outputWindow_;

public:
    explicit Simulator(std::unique_ptr<Map> map, size_t generationsToSim = 0);

    void seedFirstGeneration(size_t numOfAcacias);

    void iterate(size_t numOfIterations) const;

    void runSimulation() const;
};


#endif //IMS_SIMULATOR_H