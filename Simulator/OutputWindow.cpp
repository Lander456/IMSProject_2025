//
// Created by tadeas on 2025-12-02.
//

#include "../includes/OutputWindow.h"

class Simulator;

bool OutputWindow::OnUserCreate() {
    drawMap();
    return true;
}

bool OutputWindow::OnUserUpdate(float fElapsedTime) {
    static float accumulatedTime = 0.0f;
    constexpr float targetFrameTime = 1.0f / 60.0f;

    accumulatedTime += fElapsedTime;

    while (accumulatedTime >= targetFrameTime) {
        simulator_->iterate(1);

        accumulatedTime -= targetFrameTime;
        drawMap();
    }
    return true;
}

void OutputWindow::drawMap() {
    for (size_t y = 0; y < map_->getHeight(); y++) {
        for (size_t x = 0; x < map_->getWidth(); x++) {
            SetPixelMode(olc::Pixel::Mode::NORMAL);
            Draw(static_cast<int32_t>(x), static_cast<int32_t>(y), terrainColours[map_->at(x, y)->terrain.getType()]);
            SetPixelMode(olc::Pixel::Mode::ALPHA);
            Draw(static_cast<int32_t>(x), static_cast<int32_t>(y), speciesColours[map_->at(x, y)->vegetation.getSpecies()]);
        }
    }
}

void OutputWindow::init(Map* map, Simulator* simulator) {
    map_ = map;
    simulator_ = simulator;
}
