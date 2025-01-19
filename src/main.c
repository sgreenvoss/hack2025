#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>

// Function declarations
unsigned int create_shader_program(); 
void processInput(GLFWwindow* window); 

// Shader compilation and error checking
void check_shader_compile(unsigned int shader);
void check_program_link(unsigned int program);

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

    // Set up buffers (VBO, EBO)
    unsigned int VBO, EBO;
    float vertices[] = {
        // Position          // Color
        0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Top
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom Left
        0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // Bottom Right
    };
    unsigned int indices[] = {
        0, 1, 2  // Single triangle
    };

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Define vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window); // Handle input

        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the object
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        // Swap buffers
        glfwSwapBuffers(window);

        // Poll for events
        glfwPollEvents();
    }

    // Clean up and exit
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// Create and compile shader program
unsigned int create_shader_program() {
    const char* vertexShaderSource = "#version 120\n"
        "attribute vec3 aPos;\n"
        "attribute vec3 aColor;\n"
        "varying vec3 ourColor;\n"
        "void main() {\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "   ourColor = aColor;\n"
        "}";

    const char* fragmentShaderSource = "#version 120\n"
        "varying vec3 ourColor;\n"
        "void main() {\n"
        "   gl_FragColor = vec4(ourColor, 1.0);\n"
        "}";

    // Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    check_shader_compile(vertexShader);

    // Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    check_shader_compile(fragmentShader);

    // Shader Program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    check_program_link(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

// Check shader compilation status
void check_shader_compile(unsigned int shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::COMPILATION_FAILED\n%s\n", infoLog);
    }
}

// Check program linking status
void check_program_link(unsigned int program) {
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("ERROR::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }
}

// Handle input
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1); // Close the window when ESC is pressed
    }
}
