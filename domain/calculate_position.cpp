#include <math.h>
#include "calculate_position.hpp"

const static long double PI = 3.141592653589793238462643383279502884L;
const static long double TO_RAD = PI/180.0f;

Position calculate_position(
    const Position& current_position,
    const Orientation& current_orientation,
    const int distance) {
    auto angleInRads = current_orientation.degrees * TO_RAD;
    return Position {
        (float)(current_position.X + (distance * sin(angleInRads))), 
        (float)(current_position.Y + (distance * cos(angleInRads)))
    };
}