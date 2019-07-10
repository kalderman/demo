#ifndef __ADVANCE_TURTLE_H__
#define __ADVANCE_TURTLE_H__

#include <variant>
#include "turtle.hpp"
#include "turtle_events.hpp"

Turtle advance_turtle(
    const Turtle& current,
    const std::variant<Move, Rotate, TogglePen>& event);

#endif // __ADVANCE_TURTLE_H__