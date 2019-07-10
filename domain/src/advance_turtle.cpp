#include "advance_turtle.h"

#include <variant>

#include "turtle_events.hpp"
#include "match.h"
#include "calculate_position.h"

using namespace std;

Turtle advance_turtle(
    const Turtle& current,
    const variant<Move, Rotate, TogglePen>& event) {
    return visit(match {
            [&current](const Move& arg) { 
                return Turtle { 
                    current.pen, 
                    current.orientation, 
                    calculate_position(
                        current.position, 
                        current.orientation, 
                        Move::Distance) 
                }; 
            },
            [&current](const Rotate& arg) { 
                return Turtle {
                    current.pen,
                    *current.orientation.apply(arg),
                    current.position
                }; 
            },
            [&current](const TogglePen& arg) { 
                return Turtle{
                    visit(match {
                        [](const Up& _) { return (variant<Up, Down>) Down(); },
                        [](const Down& _) { return (variant<Up, Down>) Up(); }
                    },
                    current.pen),
                    current.orientation,
                    current.position
                }; 
            },
        }, 
        event);
}
