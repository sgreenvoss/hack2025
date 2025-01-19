#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

// woo I love C 
int i = 2;

// Function declarations
unsigned int create_shader_program();
void processInput(GLFWwindow* window);

// Shader compilation and error checking
void check_shader_compile(unsigned int shader);
void check_program_link(unsigned int program);

// Utility functions for matrix operations
void translate(float* matrix, float x, float y, float z);
void perspective(float* matrix, float fov, float aspect, float near, float far);
void multiply_matrix(float* result, float* mat1, float* mat2);
void load_identity(float* matrix);
void transpose_matrix(float* matrix);

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Create and use shader program
    unsigned int shaderProgram = create_shader_program();
    glUseProgram(shaderProgram);

    // Define vertices and indices for a cube
    float vertices[] = {
        // Positions         // Colors
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // Front Bottom Left
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // Front Bottom Right
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // Front Top Right
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, // Front Top Left
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, // Back Bottom Left
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // Back Bottom Right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // Back Top Right
        -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f  // Back Top Left
    };

    unsigned int indices[] = {
        // Front
        0, 1, 2, 2, 3, 0,
        // Back
        4, 5, 6, 6, 7, 4,
        // Left
        0, 4, 7, 7, 3, 0,
        // Right
        1, 5, 6, 6, 2, 1,
        // Top
        3, 2, 6, 6, 7, 3,
        // Bottom
        0, 1, 5, 5, 4, 0
    };

    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Set up transformation matrices (model, view, projection)
    float model[16], view[16], projection[16];
    load_identity(model);
    load_identity(view);
    load_identity(projection);

    // Apply view transformation
    translate(view, 0.0f, 0.0f, -5.0f);

    // Apply projection transformation
    perspective(projection, 45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window); // Handle input

        // Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glBindVertexArray(VAO);

        // Set the transformation matrices for the shader
        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection);

        // Render the cube
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // Swap buffers
        glfwSwapBuffers(window);

        // Poll for events
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

unsigned int create_shader_program() {
    // Vertex Shader source code
    const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
    "   ourColor = aColor;\n"
    "}\0";

    // Fragment Shader source code
    const char* fragmentShaderSource = "#version 330 core\n"
    "in vec3 ourColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(ourColor, 1.0f);\n"
    "}\n\0";

    // Compile shaders and create program
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    check_shader_compile(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    check_shader_compile(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    check_program_link(shaderProgram);

    // Clean up shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void check_shader_compile(unsigned int shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Shader compilation failed\n%s\n", infoLog);
    }
}

void check_program_link(unsigned int program) {
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("Program linking failed\n%s\n", infoLog);
    }
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Utility functions for matrix operations

void load_identity(float* matrix) {
    for (int i = 0; i < 16; i++) {
        matrix[i] = (i % 5 == 0) ? 1.0f : 0.0f;
    }
}

void translate(float* matrix, float x, float y, float z) {
    load_identity(matrix);
    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
}

void perspective(float* matrix, float fov, float aspect, float near, float far) {
    float tanHalfFovy = tanf(fov / 2.0f);
    matrix[0] = 1.0f / (aspect * tanHalfFovy);
    matrix[5] = 1.0f / tanHalfFovy;
    matrix[10] = -(far + near) / (far - near);
    matrix[11] = -1.0f;
    matrix[14] = -(2.0f * far * near) / (far - near);
    matrix[15] = 0.0f;
}

void multiply_matrix(float* result, float* mat1, float* mat2) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i * 4 + j] = 0;
            for (int k = 0; k < 4; k++) {
                result[i * 4 + j] += mat1[i * 4 + k] * mat2[k * 4 + j];
            }
        }
    }
}