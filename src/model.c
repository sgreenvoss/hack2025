#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

<<<<<<< HEAD





float * GenerateGrid()
{
    //MALLOC #of vertices in Grid 
    float * Grid = (float *)malloc(sizeof(float) * ((2*MAX_X)*(2*MAX_Y)/RES)*3);
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

void applyParaboloid(float** gridptr, int a, int b, int c)
{
    /*
    Applies the function: 
        z/c = (x^2 / a^2) + (y^2 / b^2)
    to each point in the grid
    */
    float *grid = *gridptr; // Dereference pointer to grid
    
    for(int i=0; i<(((2*MAX_X)*(2*MAX_Y)/RES)*3)+1; i++) { //FIXME
        /* Calculates the z value for each (x,y) pair in grid */
        float x = *grid;
        grid++;
        float y = *grid;
        grid++;
        //Apply function to (x,y) values
        *grid = c * ((pow(x, 2)*pow(a, 2)) * (pow(y, 2)*pow(b, 2)));
        grid++;
    }
}

void normalize(float **gridptr)
{

}
//void ** GeneratePoints(xStart, xEnd, xRes, yStart, yEnd, yRes, void *

int main()
{
    float* tmp = GenerateGrid();
    applyParaboloid(&tmp, 1, 4, 4);

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
=======
void check_shader_compile(unsigned int shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::COMPILATION_FAILED\n%s\n", infoLog);
    }
}

void check_program_link(unsigned int program) {
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("ERROR::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
>>>>>>> fe26d4bcc59e602356c00360a7d8fe3f62f9ed7f
    }
}