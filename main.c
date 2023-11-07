#include <stdio.h>

#include <math.h>

#include "glad.h"
#include <GLFW/glfw3.h>

#include "fileio.h"

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

// Compile Shader
unsigned int compileShader(unsigned int shaderType, const char *shaderSource)
{
    int success;
    char infoLog[512];

    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Shader Failed To Compile: %s\n", infoLog);
    }

    return shader;
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

    // Read Shaders
    char *vertexShaderSource = readFile("vertexShader.glsl");
    char *fragmentShaderSource = readFile("fragmentShader.glsl");

    // Compile Shaders
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // Link Shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Clean Up Shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    freeFile(vertexShaderSource);
    freeFile(fragmentShaderSource);

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
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Main Loop
    while (!glfwWindowShouldClose(window))
    {
        // Process Input
        processInput(window);

        // Clear Buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Activate Shader
        glUseProgram(shaderProgram);

        // Update shader
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // Draw Triangle
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