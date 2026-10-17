#include "glad.h"
#include "glfw3.h"

#include <iostream>
#include <cmath>

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform float scaleX;\n"
    "uniform float scaleY;\n"
    "uniform float moveX;\n"
    "uniform float moveY;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos.x * scaleX + moveX,\n"
    "                       aPos.y * scaleY + moveY,\n"
    "                       aPos.z, 1.0);\n"
    "}\n";

const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = ourColor;\n"
    "}\n";

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
        SCR_WIDTH, SCR_HEIGHT, "0432410005101020", NULL, NULL
    );

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        -0.3f, -0.2f, 0.0f,
         0.3f, -0.2f, 0.0f,
         0.3f,  0.2f, 0.0f,

        -0.3f, -0.2f, 0.0f,
         0.3f,  0.2f, 0.0f,
        -0.3f,  0.2f, 0.0f
    };

    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    int colorLoc = glGetUniformLocation(shaderProgram, "ourColor");
    int sxLoc = glGetUniformLocation(shaderProgram, "scaleX");
    int syLoc = glGetUniformLocation(shaderProgram, "scaleY");
    int mxLoc = glGetUniformLocation(shaderProgram, "moveX");
    int myLoc = glGetUniformLocation(shaderProgram, "moveY");

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float t = glfwGetTime();

        float color = (sin(t) + 1.0f) / 2.0f;

        float scaleX = 1.0f + 0.7f * sin(t);
        float scaleY = 1.0f + 0.5f * cos(t);

        float moveX = 0.4f * sin(t);
        float moveY = 0.3f * cos(t);

        glUseProgram(shaderProgram);

        glUniform4f(colorLoc, 1.0f, color, color, 1.0f);

        glUniform1f(sxLoc, scaleX);
        glUniform1f(syLoc, scaleY);
        glUniform1f(mxLoc, moveX);
        glUniform1f(myLoc, moveY);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
