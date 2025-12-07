cmake_minimum_required(VERSION 4.0)
project(IMS)

set(CMAKE_CXX_STANDARD 20)

add_executable(IMS
        main.cpp
        includes/SpeciesEnum.h
        Species/SpeciesInfo.cpp
        includes/SpeciesInfo.h
        Species/SpeciesRegistry.cpp
        includes/SpeciesRegistry.h
        includes/Soil.h
        Cell/Vegetation.cpp
        includes/Vegetation.h
        includes/TerrainTypesEnum.h
        includes/Terrain.h
        Cell/Cell.cpp
        includes/Cell.h
        Map/Map.cpp
        includes/Map.h
        Map/MapParser.cpp
        includes/MapParser.h
        includes/Config.h
        ArgParser/ArgParser.cpp
        includes/ArgParser.h
        Simulator/Simulator.cpp
        includes/Simulator.h
        includes/Errnos.h
        Simulator/OutputWindow.cpp
        includes/OutputWindow.h
        includes/Colours.h
        includes/Colours.h
        includes/Colours.h
        includes/MapModeEnum.h
)

target_link_libraries(IMS
        X11
        GL
        GLX
        png
        pthread
        dl
)