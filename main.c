#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {

    // Initialize GLFW.
    if (!glfwInit())
    {
        return -1;
    }

    // Create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Window", NULL, NULL);

    // If window creation failed, terminate.
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make window current context.
    glfwMakeContextCurrent(window);

    // Define vertex data for triangle
    GLfloat verticies[] = {
        0.0f,   0.5f,   // Top vertex
        -0.5f,  -0.5f,  // Bottom-left vertex
        0.5f,   -0.5f   // Bottom-right vertex
    };

    // Create a Vertex Buffer Object (VBO)
    GLuint VBO;
    //glGenBuffers(1, &VBO); need to figure out GLEW
    

    // Main loop.
    while (!glfwWindowShouldClose(window)) {

        // RENDER HERE
        
        // Swap front and back buffers.
        glfwSwapBuffers(window);

        // Poll and process events.
        glfwPollEvents();
    }

    // Exit with grace.
    glfwTerminate();
    return 0;
}