#include <math.h>
#include "calculate_position.h"

Position calculate_position(
    const Position& p,
    const Orientation& o,
    const int distance) {
    const static long double pi = 3.141592653589793238462643383279502884L;
    auto angleInRads = o.degrees * (pi/180.0f);
    auto x = (float) (p.X + (distance * sin(angleInRads)));
    auto y = (float) (p.Y + (distance * cos(angleInRads)));
    return Position {x, y};
}