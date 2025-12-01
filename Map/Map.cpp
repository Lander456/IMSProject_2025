//
// Created by tadeas on 2025-11-27.
//

#include "../includes/Map.h"
#include <queue>

Map::Map(const size_t w, const size_t h) : width(w), height(h) {
    grid.resize(h);
    for (auto& row : grid) {
        row.resize(width);
    }
}

std::unique_ptr<Cell>& Map::at(const size_t x, const size_t y) {
    return grid[y][x];
}

std::vector<Cell*> Map::getCellsInRadius(const int cellX, const int cellY, const int radius) {
    std::vector<Cell*> cells;

    if(radius <= 0) return cells;

    const int minX = std::max(cellX-radius,0);
    const int maxX = std::min(cellX+radius, static_cast<int>(width) -1);
    const int minY = std::max(cellY-radius, 0);
    const int maxY = std::min(cellY+radius, static_cast<int>(height)-1);

    for(int x = minX; x <= maxX; x++){
        for(int y= minY; y <= maxY; y++){

            const int distanceX = x - cellX;
            const int distanceY = y - cellY;

            if(distanceX*distanceX + distanceY*distanceY <= radius*radius){
                cells.push_back(grid[x][y].get());
            }
        }
    }

    return cells;
}

Cell* Map::findFloodDirectionNeighbor(int cellX, int cellY){

    if(cellX >= static_cast<int>(width) || cellY >= static_cast<int>(height) || cellX < 0 || cellY < 0) return nullptr;

    std::queue<std::pair<int,int>> queue;
    std::vector<std::vector<std::pair<int,int>>> explored(width, std::vector<std::pair<int,int>>(height, {-1,-1}));
    std::vector<std::vector<bool>> isExplored(width, std::vector<bool>(height, false));

    const int dirs[4][2] = {
        { 0,-1}, {-1, 0}, { 1, 0}, { 0, 1}
    };

    queue.push({cellX, cellY});
    isExplored[cellX][cellY] = true;

    //BFS
    while(!queue.empty()){

        //pop queue elemnt
        auto [x, y] = queue.front();
        queue.pop();

        //explore element
        Cell* c = grid[x][y].get();
        if(c->terrain.getType() == TerrainTypesEnum::Water){ //water found

            std::pair<int,int> step = {x,y};
            while(explored[step.first][step.second] != std::make_pair(cellX, cellY)){
                step = explored[step.first][step.second];
                if (step.first == -1) break;
            }
            return grid[step.first][step.second].get();
        }

        //add unexplored neigbors from queue
        for(auto& d : dirs){
            const int newCellX = x + d[0];
            const int newCellY = y + d[1];

             if (newCellX < 0 || newCellY < 0 || newCellX >= static_cast<int>(width) || newCellY >= static_cast<int>(height))
                continue;

            if(!isExplored[newCellX][newCellY]){
                isExplored[newCellX][newCellY] = true;
                explored[newCellX][newCellY] = {x,y};
                queue.push({newCellX, newCellY});
            }
        }
    }

    return nullptr;
}