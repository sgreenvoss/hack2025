#include <stdio.h>
#include "model.h"

// Function to print a vertex
void printVertex(v V) {
    printf("<%f, %f, %f>\n", V.x, V.y, V.z);
}

// If you want to test this file separately, you can temporarily include a main function here.
// Remember to remove or comment it out when integrating into your main project.
/*
int main() {
    // Example usage of printVertex for testing
    v testVertex = {1.0f, 2.0f, 3.0f};
    printVertex(testVertex);
    return 0;
}
*/