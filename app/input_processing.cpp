#include "input_processing.hpp"
#include "advance_turtle.hpp"
#include "turtle_events.hpp"
#include <GLFW/glfw3.h>
#include <optional>

void update_turtle_log(vector<Turtle>& turtle_log, const variant<Move, Rotate, TogglePen>& event){
    turtle_log.push_back(advance_turtle(turtle_log.back(), event));
}

optional<variant<Move, Rotate, TogglePen>> convert_input_to_turtle_event(int key, int action){
    auto press_or_repeat = (action == GLFW_PRESS || action == GLFW_REPEAT);
    if (key == GLFW_KEY_SPACE && press_or_repeat)
        return TogglePen();
    if (key == GLFW_KEY_UP && press_or_repeat)
        return Move();
    if (key == GLFW_KEY_LEFT && press_or_repeat)
        return Rotate(Rotate::Counterclockwise());
    if (key == GLFW_KEY_RIGHT && press_or_repeat)
        return Rotate(Rotate::Clockwise());
    return {};
}

void update_turtle_log(int key, int action, vector<Turtle>& turtle_log){
    auto maybe_event = convert_input_to_turtle_event(key, action);
    if(maybe_event.has_value()) update_turtle_log(turtle_log, maybe_event.value());
}
