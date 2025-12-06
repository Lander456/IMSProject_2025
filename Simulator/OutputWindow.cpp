//
// Created by tadeas on 2025-12-02.
//

#include "../includes/OutputWindow.h"
#include "../includes/Config.h"

#include <map>

class Simulator;

bool OutputWindow::OnUserCreate() {
    drawMap();
    return true;
}

bool OutputWindow::OnUserUpdate(const float fElapsedTime) {

    if (GetKey(olc::Key::SPACE).bPressed) {
        if (manualStepping_ && (simulator_->generationsSimulated_ < simulator_->generationsToSim_) || simulator_->generationsToSim_ == -1) {
            simulator_->iterate(1);
            simulator_->generationsSimulated_++;

            drawMap();
            return true;
        }
    }

    if (GetKey(olc::Key::N).bPressed) {
        mapMode_ = MapModes::NITROGEN;

        drawMap();
        return true;
    }

    if (GetKey(olc::Key::V).bPressed) {
        mapMode_ = MapModes::VEGETATION;

        drawMap();
        return true;
    }

    if (GetKey(olc::Key::M).bPressed) {
        mapMode_ = MapModes::MOISTURE;

        drawMap();
        return true;
    }

    if (GetKey(olc::Key::R).bPressed && resetMsgShown_) {
        simulator_->resetSim();
    }

    if (!manualStepping_ && (simulator_->generationsSimulated_ < simulator_->generationsToSim_) || simulator_->generationsToSim_ == -1) {
        static float accumulatedTime = 0.0f;
        constexpr float targetFrameTime = 1.0f / 60.0f;

        accumulatedTime += fElapsedTime;

        while (accumulatedTime >= targetFrameTime) {
            simulator_->iterate(1);
            simulator_->generationsSimulated_++;

            accumulatedTime -= targetFrameTime;
            drawMap();
        }
        return true;
    }

    if (simulator_->generationsSimulated_ == simulator_->generationsToSim_ && !resetMsgShown_) {
        resetMsgShown_ = true;

        std::cout << "Simulation finished, to reset the simulation press R!" << std::endl;
    }

    return true;
}

void OutputWindow::drawMap() {
    for (size_t y = 0; y < map_->getHeight(); y++) {
        for (size_t x = 0; x < map_->getWidth(); x++) {
            SetPixelMode(olc::Pixel::Mode::NORMAL);
            switch (mapMode_) {
                case MapModes::VEGETATION: {
                    Draw(static_cast<int32_t>(x), static_cast<int32_t>(y), speciesColours[map_->at(x, y)->vegetation->getSpecies()]);
                    break;
                }
                case MapModes::NITROGEN: {
                    const auto currentCell = map_->at(x, y).get();

                    Draw(static_cast<int32_t>(x), static_cast<int32_t>(y), getGradientColour(Colours::WHITE, Colours::BLACK_VOID, currentCell->soil.getNitrate()/Config::maxSoilNitre));
                    break;
                }
                case MapModes::MOISTURE: {
                    const auto currentCell = map_->at(x, y).get();

                    Draw(static_cast<int32_t>(x), static_cast<int32_t>(y), getGradientColour(Colours::WHITE, Colours::WATER_BLUE, currentCell->soil.getMoisture()/Config::floodTreshold));
                    break;
                }
            }
        }
    }
}

olc::Pixel OutputWindow::getGradientColour(const olc::Pixel lowColour, const olc::Pixel highColour, float normalizedVal) {

    normalizedVal = std::clamp(normalizedVal, 0.0f, 1.0f);

    const auto colour = olc::Pixel(static_cast<uint8_t>(lowColour.r + (highColour.r - lowColour.r) * normalizedVal),
        static_cast<uint8_t>(lowColour.g + (highColour.g - lowColour.g) * normalizedVal),
        static_cast<uint8_t>(lowColour.b + (highColour.b - lowColour.b) * normalizedVal),
        static_cast<uint8_t>(lowColour.a + (highColour.a - lowColour.a) * normalizedVal));

    return colour;
}

void OutputWindow::init(Map* map, Simulator* simulator, const bool stepMode) {
    map_ = map;
    simulator_ = simulator;
    manualStepping_ = stepMode;
}
