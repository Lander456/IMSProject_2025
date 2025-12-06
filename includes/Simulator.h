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
    std::unique_ptr<Map> map_;
    std::mt19937 generator_;
    std::unique_ptr<OutputWindow> outputWindow_;
    std::vector<std::pair<size_t, size_t>> acaciaCoords;

public:
    size_t generationsToSim_;
    size_t generationsSimulated_;
    size_t numOfAcacias_ = 0;

    explicit Simulator(std::unique_ptr<Map> map, ssize_t generationsToSim, bool manualMode, size_t numOfAcacias);

    void seedFirstGeneration(size_t numOfAcacias);

    void iterate(ssize_t numOfIterations) const;

    void runSimulation() const;

    void resetSim();
};


#endif //IMS_SIMULATOR_H