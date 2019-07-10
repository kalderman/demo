#ifndef __CALCULATE_POSITION_H__
#define __CALCULATE_POSITION_H__

#include "position.h"
#include "orientation.h"

Position calculate_position(
    const Position& p,
    const Orientation& o,
    const int distance);

#endif // __CALCULATE_POSITION_H__