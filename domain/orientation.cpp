#include "orientation.hpp"

#include <variant>
#include <math.h>

#include "turtle_events.hpp"
#include "match.hpp"

using namespace std;

Orientation::Orientation(int angle, Rotate r) : degrees(apply(angle, r)) { }
Orientation::Orientation() { }
Orientation::Orientation(const Rotate& r) : degrees(apply(0, r)) { }

std::unique_ptr<Orientation> Orientation::apply(const Rotate& rhs) const {
    return std::make_unique<Orientation>(Orientation(degrees, rhs));
}

bool Orientation::is_clockwise(const Rotate& r) {
    return visit(match {
            [](const Rotate::Clockwise& _) { return true; },
            [](const Rotate::Counterclockwise& _){ return false; }
        },
        r.direction);
}

int Orientation::apply(int angle, const Rotate& r) {
    return (angle + (is_clockwise(r) ? Rotate::Degrees : -Rotate::Degrees)) % 360;
}
