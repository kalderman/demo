#ifndef __ORIENTATION_H__
#define __ORIENTATION_H__

#include "turtle_events.hpp"
#include <memory>

class Orientation
{
    private:
    Orientation(int angle, Rotate r);

    public:
    const int degrees = 0;
    Orientation();
    Orientation(const Rotate& r);

    std::unique_ptr<Orientation> apply(const Rotate& rhs) const;

    private:
    static bool is_clockwise(const Rotate& r);
    static int apply(int angle, const Rotate& r);
};

#endif // __ORIENTATION_H__
