#ifndef __TURTLE_HPP__
#define __TURTLE_HPP__

#include <variant>

#include "orientation.hpp"
#include "position.hpp"
#include "turtle_events.hpp"
#include "match.hpp"

struct Turtle {
    const std::variant<Up, Down> pen = Up();
    const Orientation orientation = Orientation();
    const Position position = Position();
};

inline bool is_pen_up(const Turtle& t){
    return visit(match {
        [](const Up& _) { return true; },
        [](const Down& _) { return false; }
    },
    t.pen);
}

inline bool is_pen_down(const Turtle& t){
    return !is_pen_up(t);
}

#endif // __TURTLE_HPP__