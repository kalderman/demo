#include <math.h>
#include "calculate_position.h"

Position calculate_position(
    const Position& p,
    const Orientation& o,
    const int distance) {
    auto angleInRads = o.degrees * (M_PI/180.0f);
    auto x = (float) (p.X + (distance * sin(angleInRads)));
    auto y = (float) (p.Y + (distance * cos(angleInRads)));
    return Position {x, y};
}