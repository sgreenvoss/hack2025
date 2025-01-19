#include <stdio.h>
#include "model.h"
#include <math.h>

#define PI 3.1415926



//in this file I want to test writing points of a function


float* Circle(float radius,float x_dif,float y_dif,float z_dif) {
	//my center will be determined by the difference in each axis
	//thus: no difference -> (0,0,0) y_diff = 2 -> (0,2,0)

    float angle_step = 2 * PI / RES;  // Angle step in radians

    printf("x\ty\n");  // Header for the output

    for (int i = -radius; i < radius + RES; i++) {
        float theta = i * angle_step;  // Current angle in radians
        float x = radius * cos(theta);  // x-coordinate
        float y = radius * sin(theta);

	
}

//float* Pyramid() {

//}


//int main() {
	//this is a test function that I want to use to write math to veritices

//}
