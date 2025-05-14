#ifndef __TURTLE_EVENTS_HPP__
#define __TURTLE_EVENTS_HPP__

#include <variant>

struct Move { static const int Distance = 10; };

class Rotate { 
    public:
    struct Clockwise {};
    struct Counterclockwise {};

    const static int Degrees = 10; 

    const std::variant<Clockwise, Counterclockwise> direction;

    Rotate(Clockwise d) : direction(d) { }
    Rotate(Counterclockwise d) : direction(d) { }
};

struct Up {};

struct Down {};

struct TogglePen {};

#endif // __TURTLE_EVENTS_HPP__
