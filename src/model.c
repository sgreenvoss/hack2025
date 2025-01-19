// #define YSTART -10
// #define YEND 10
// #define XSTART -10
// #define XEND 10
// #define GRID_RES 0.1
#include "model.h"






float * GenerateGrid()
{
    //MALLOC #of vertices in Grid 
    float * Grid = (float *)malloc(sizeof(float) * (NUM_PTS*3);
    float * index = Grid;
    for (float i=-MAX_X; i < MAX_X+RES; i+=RES)
    {
        for (float j=-MAX_Y; j < MAX_Y+RES; j+= RES)
        {
            *index = i;
            index++;
            *index = j;
            index++;
            *index = 0; //Z coord
            index++;
        }
    }
    return Grid;
}

void applyParaboloid(float** gridptr, int a, int b, int c, float *z_max)
{
    /*
    Applies the function: 
        z/c = (x^2 / a^2) + (y^2 / b^2)
    to each point in the grid
    */
    float *grid = *gridptr; // Dereference pointer to grid

    float max = 0.0f;
    
    for(int i=0; i<(NUM_PTS+1); i++) { //FIXME
        /* Calculates the z value for each (x,y) pair in grid */
        float x = *grid;
        grid++;
        float y = *grid;
        grid++;
        //Apply function to (x,y) values
        *grid = c * ((pow(x, 2)*pow(a, 2)) * (pow(y, 2)*pow(b, 2)));
        if *grid > max
        {
            max = *grid;
        }
        grid++;
    }
    *z_max = max;
}

void normalize(float **gridptr)
{

}
//void ** GeneratePoints(xStart, xEnd, xRes, yStart, yEnd, yRes, void *

int main()
{
    float* tmp = GenerateGrid();
    float z_max;
    applyParaboloid(&tmp, 1, 4, 4, &z_max);

    for (int i=0; i<=20; i++)
    {
        for (int j=0; j<=20; j++)
        {
            // printf("vertex(%.2f, ", *tmp);
            // tmp++;
            // printf("%.2f, ", *tmp);
            // tmp++;
            // printf("%.2f) ", *tmp);
            // tmp++;
            printf("(%.2f,", *tmp);
            tmp++;
            printf("%.2f,", *tmp);
            tmp++;
            printf("%.2f) ", *tmp);
            tmp++;
        }
        printf("\n");
    }
}