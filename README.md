[![Build Status](https://travis-ci.com/kalderman/demo.svg?branch=master)](https://travis-ci.com/kalderman/demo)

## Turtle graphics
This demo is an interactive OpenGL implementation of [turtle graphics](https://en.wikipedia.org/wiki/Turtle_graphics).

### Basic requirements:
- Move in the current direction.
- Turn clockwise or counterclockwise to change direction.
- Put the pen down or up. 
- When the pen is down, moving the turtle draws a line.

### Keys:
- Up: Move.
- Left: Rotate counterclockwise.
- Right: Rotate clockwise.
- Space: toggle pen.

### TODO (probably won't have time):
- Get this to build on AppVeyor (Windows).
- Draw a turtle (currently a triangle).
- Stop the turtle at the edge of the window or pass to other side.
- Test some of the drawing/state related code.