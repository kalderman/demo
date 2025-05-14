#include <iostream>
#include <vector>

#include "openglwindow.hpp"
#include "turtle.hpp"
#include "drawing.hpp"
#include "input_processing.hpp"

using namespace std;


int main()
{
    auto turtle_log = vector<Turtle> { Turtle() };

    auto result = OpenGlWindow(
            [&](int key, int action){ update_turtle_log(key, action, turtle_log); }, 
            [&](){ update_canvas(turtle_log); })
        .Show();
 
    if(result.has_value()){
        visit(match {
            [](const InitializationFailed& _) { cerr << "Init failed" << endl; },
            [](const WindowOrOpenGlContextCreationFailed& _){ cerr << "Widnow or OpenGL context creation failed" << endl; }
        },
        result.value());
        return -1;
    }
    return 0;
}
