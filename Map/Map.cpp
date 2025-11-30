//
// Created by tadeas on 2025-11-27.
//

#include "../includes/Map.h"
#include <queue>

Cell & Map::at(const size_t x, const size_t y) {
    return *grid[x][y];
}

std::vector<Cell*> Map::getCellsInRadius(int cellX, int cellY, int radius) {
    std::vector<Cell*> cells;

    if(radius <= 0) return cells;

    int minX = std::max(cellX-radius,0);
    int maxX = std::min(cellX+radius, (int)width -1);
    int minY = std::max(cellY-radius, 0);
    int maxY = std::min(cellY+radius, (int)height-1);

    for(int x = minX; x <= maxX; x++){
        for(int y= minY; y <= maxY; y++){
            
            int distanceX = x - cellX;
            int distanceY = y - cellY;

            if(distanceX*distanceX + distanceY*distanceY <= radius*radius){
                cells.push_back(grid[x][y].get());
            }
        }
    }

    return cells;
}

Cell* Map::findFloodDirectionNeighbor(int cellX, int cellY){

    if(cellX >= (int)width || cellY >= (int)height || cellX < 0 || cellY < 0) return nullptr;

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
            int newCellX = x + d[0];
            int newCellY = y + d[1];

             if (newCellX < 0 || newCellY < 0 || newCellX >= (int)width || newCellY >= (int)height)
                continue;
        }

        
    }

    return nullptr;
}