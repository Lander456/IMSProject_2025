cmake_minimum_required(VERSION 4.0)
project(IMS)

set(CMAKE_CXX_STANDARD 20)

add_executable(IMS main.cpp
        includes/SpeciesEnum.h
        Species/SpeciesInfo.cpp
        includes/SpeciesInfo.h
        Species/SpeciesRegistry.cpp
        includes/SpeciesRegistry.h
        Cell/Soil.cpp
        includes/Soil.h
        Cell/Vegetation.cpp
        includes/Vegetation.h
        includes/TerrainTypesEnum.h
        Cell/Terrain.cpp
        includes/Terrain.h
        Cell/Cell.cpp
        includes/Cell.h
)
