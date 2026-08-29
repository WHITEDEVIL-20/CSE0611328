#include "glad.h"
#include "glfw3.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Window settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Vertex Shader
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}\0";

// Fragment Shader for Cyan Square
const char* cyanFragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n" // Cyan
    "}\n\0";

// Fragment Shader for Magenta Triangle
const char* magentaFragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n" // Magenta
    "}\n\0";


int main()
{
    // Initialize GLFW
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(
        SCR_WIDTH,
        SCR_HEIGHT,
        "AKM Hamja Akand Fahim",
        NULL,
        NULL
    );

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // Create Vertex Shader

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    glCompileShader(vertexShader);


    // Create Cyan Fragment Shader

    unsigned int cyanFragmentShader =
        glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(
        cyanFragmentShader,
        1,
        &cyanFragmentShaderSource,
        NULL
    );

    glCompileShader(cyanFragmentShader);


    // Create Magenta Fragment Shader

    unsigned int magentaFragmentShader =
        glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(
        magentaFragmentShader,
        1,
        &magentaFragmentShaderSource,
        NULL
    );

    glCompileShader(magentaFragmentShader);

    // Cyan Shader Program

    unsigned int cyanShaderProgram = glCreateProgram();

    glAttachShader(cyanShaderProgram, vertexShader);
    glAttachShader(cyanShaderProgram, cyanFragmentShader);

    glLinkProgram(cyanShaderProgram);

    // Magenta Shader Program

    unsigned int magentaShaderProgram = glCreateProgram();

    glAttachShader(magentaShaderProgram, vertexShader);
    glAttachShader(magentaShaderProgram, magentaFragmentShader);

    glLinkProgram(magentaShaderProgram);


    // Delete shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(cyanFragmentShader);
    glDeleteShader(magentaFragmentShader);


    // CYAN SQUARE VERTICES

    float squareVertices[] = {

        // Top Right
         0.5f,  0.5f, 0.0f,

        // Bottom Right 
         0.5f, -0.5f, 0.0f,

        // Bottom Left
        -0.5f, -0.5f, 0.0f,

        // Top Left
        -0.5f,  0.5f, 0.0f
    };

    unsigned int squareIndices[] = {

        0, 1, 3,
        1, 2, 3
    };


    unsigned int squareVAO, squareVBO, squareEBO;

    glGenVertexArrays(1, &squareVAO);
    glGenBuffers(1, &squareVBO);
    glGenBuffers(1, &squareEBO);

    glBindVertexArray(squareVAO);

    glBindBuffer(GL_ARRAY_BUFFER, squareVBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(squareVertices),
        squareVertices,
        GL_STATIC_DRAW
    );

    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        squareEBO
    );

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(squareIndices),
        squareIndices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);


    // MAGENTA TRIANGLE

    float triangleVertices[] = {

        // Left 
        -0.5f,  0.5f, 0.0f,
        // Right 
         0.0f, 0.75f, 0.0f,
        // Top 
         0.5f,  0.5f, 0.0f
    };


    unsigned int triangleVAO, triangleVBO;

    glGenVertexArrays(1, &triangleVAO);
    glGenBuffers(1, &triangleVBO);

    glBindVertexArray(triangleVAO);

    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(triangleVertices),
        triangleVertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);


    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(
            1.0f,
            1.0f,
            1.0f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(cyanShaderProgram);

        glBindVertexArray(squareVAO);

        glDrawElements(
            GL_TRIANGLES,
            6,
            GL_UNSIGNED_INT,
            0
        );


        glUseProgram(magentaShaderProgram);

        glBindVertexArray(triangleVAO);

        glDrawArrays(
            GL_TRIANGLES,
            0,
            3
        );


        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &squareVAO);
    glDeleteBuffers(1, &squareVBO);
    glDeleteBuffers(1, &squareEBO);

    glDeleteVertexArrays(1, &triangleVAO);
    glDeleteBuffers(1, &triangleVBO);

    glDeleteProgram(cyanShaderProgram);
    glDeleteProgram(magentaShaderProgram);


    glfwTerminate();

    return 0;
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}


void framebuffer_size_callback(
    GLFWwindow* window,
    int width,
    int height
)
{
    glViewport(0, 0, width, height);
}