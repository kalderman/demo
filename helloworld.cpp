#include <iostream>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

using namespace std;
using namespace gl;


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // create context, e.g. using GLFW, Qt, SDL, GLUT, ...
    glfwSetErrorCallback([](int _, const char* description) { fprintf(stderr, "Error: %s\n", description); });

    if (!glfwInit())
    {
        // Initialization failed
        cout << "Init failed" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    auto* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        // Window or OpenGL context creation failed
        cout << "Widnow or OpenGL context creation failed" << endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(
        window,
        [](GLFWwindow* _, int width, int height){ glViewport(0, 0, width, height); });

    // Assume context creation using GLFW
    glbinding::initialize(glfwGetProcAddress);

    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
        glLoadIdentity();                       // Reset The View

        // Keep running
        glBegin(GL_TRIANGLES);
        // ...
        glVertex3f(-1.0f, -1.0f, .0f);
        glVertex3f(1.0f, -1.0f, .0f);
        glVertex3f(.0f, 1.0f, .0f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();

        processInput(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}