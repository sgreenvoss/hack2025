// #define YSTART -10
// #define YEND 10
// #define XSTART -10
// #define XEND 10
// #define GRID_RES 0.1
#include "model.h"






v * GenerateGrid()
{
    //MALLOC #of vertices in Grid 
    v * Grid = (v *)malloc(sizeof(v) * ((2*MAX_X)*(2*MAX_Y)/RES));
    v * index = Grid;
    for (float i=-MAX_X; i <MAX_X; i+=RES)
    {
        for (float j=-MAX_Y; j < MAX_Y; j+= RES)
        {
            *index = v(i,j,0);
            index++;
        }
    }
}
//void ** GeneratePoints(xStart, xEnd, xRes, yStart, yEnd, yRes, void *

int main()
{
    v vertex = GenerateGrid();
}