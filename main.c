#include "glad.h"
#include <GLFW/glfw3.h>

#include <stdio.h>

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Shaders
const char *vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

// Process Input
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

// Window Size Callback
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    //Make sure viewport is resized when the window size is updated.
    glViewport(0, 0, width, height);
}

// Main
int main() 
{
    // Initalize and Configure GLFW - (Version 4.6, Core Profile)
    if (!glfwInit()) {
        printf("Failed to initalize GLFW.\n");
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create and Configure window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "gltest", NULL, NULL);
    if (!window) {
        printf("Failed to create window.\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initalize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initalize GLAD.\n");
        return 1;
    } 

    // Shader Compilation
    int success;
    char infoLog[512];

    // Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Vertex Shader Failed To Compile: %s\n", infoLog);
    }

    // Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("Fragment Shader Failed To Compile: %s\n", infoLog);
    }

    // Link Shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Failed to Link Shaders: %s\n", infoLog);
    }

    // Clean Up Shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Program Data
    float vertices[] = {
        0.5f,   0.5f,   0.0f,   // Top Right
        0.5f,   -0.5f,  0.0f,   // Bottom Right
        -0.5f,  -0.5f,  0.0f,   // Bottom Left
        -0.5f,  0.5f,   0.0f    // Top Left
    };
    unsigned int indices[] = {
        0, 1, 3,    // First Triangle
        1, 2, 3
    };

    // Configure Array & Buffers
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copy vertices to buffer

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // copy indices to buffer

    // Link Vertex Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Set Clear Color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    //Set To Draw Wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Main Loop
    while (!glfwWindowShouldClose(window))
    {
        // Process Input
        processInput(window);

        // Render
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Swap Buffers, Poll Events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Exit Gracefully
    printf("Exiting...\n");
    glfwTerminate();
    return 0;
}