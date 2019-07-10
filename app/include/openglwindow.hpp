#ifndef __OPENGLWINDOW_H__
#define __OPENGLWINDOW_H__

#include <optional>
#include <variant>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

using namespace std;
using namespace gl;

struct InitializationFailed {};
struct WindowOrOpenGlContextCreationFailed {};

template<typename OnInput, typename OnRender>
class OpenGlWindow
{
    private:
    const OnInput& onInput;
    const OnRender& onRender;

    public:
    OpenGlWindow(
        const OnInput& onInput,
        const OnRender& onRender) : onInput(onInput), onRender(onRender) 
    { }

    optional<variant<InitializationFailed, WindowOrOpenGlContextCreationFailed>> Show(){
        if (!glfwInit()){
            return InitializationFailed();
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        auto* window = glfwCreateWindow(640, 480, "Turtle Graphics", NULL, NULL);
        if (!window){
            return WindowOrOpenGlContextCreationFailed();
        }

        glfwSetWindowUserPointer(window, (void *)this);
        glfwSetKeyCallback(window, key_callback);

        glfwMakeContextCurrent(window);

        glfwSetFramebufferSizeCallback(
            window,
            [](GLFWwindow* _, int width, int height){ 
                glViewport(0, 0, width, height);
            });

        glbinding::initialize(glfwGetProcAddress);

        while (!glfwWindowShouldClose(window))
        {
            onRender();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();

        return {};
    }

    private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
        auto that = (OpenGlWindow *)glfwGetWindowUserPointer(window);
        that->onInput(key, action);
    }
};

#endif // __OPENGLWINDOW_H__