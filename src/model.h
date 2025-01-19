#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAX_Z 10
#define MAX_Y 10
#define MAX_X 10
#ifndef RES
#define RES 0.1
#endif

#define NUM_PTS ((2*MAX_X)*(2*MAX_Y)/RES)   //Size of buffer for (x,y,z) object

// Vertex Struct
typedef struct Vertex {
    float x;
    float y;
    float z;
} v;

