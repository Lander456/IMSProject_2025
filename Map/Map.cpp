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

Cell & Map::at(const size_t x, const size_t y) const {
    return *grid[x][y];
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

    std::queue< 
        std::pair< std::pair<int,int>, std::pair<int,int> >
    > queue;

    // [{ visited_cell{x,y}, from{x,y}}]
    std::queue< 
        std::pair< std::pair<int,int>, std::pair<int,int> >
    > explored;
    std::vector<std::vector<bool>> isExplored(width, std::vector<bool>(height, false));

    const int dirs[8][2] = {
        { 0,-1}, {-1, 0}, { 1, 0}, { 0, 1},
        {-1,-1}, { 1,-1}, {-1, 1}, { 1, 1}
    };

    queue.push({{cellX, cellY}, {cellX, cellY}});
    isExplored[cellX][cellY] = true;

    //BFS
    while(!queue.empty()){
        //pop queue elemnt
        auto [cell,prev_cell] = queue.front();
        auto [x, y] = cell;
        queue.pop();

        //explore element
        Cell* c = grid[x][y].get();
        if(c->terrain.getType() == TerrainTypesEnum::Water){ //water found
            return c;
        }

        //add unexplored neigbors from queue
        for(auto& d : dirs){
            const int newCellX = x + d[0];
            const int newCellY = y + d[1];

             if (newCellX < 0 || newCellY < 0 || newCellX >= static_cast<int>(width) || newCellY >= static_cast<int>(height))
                continue;
        }

        
    }

    return nullptr;
}