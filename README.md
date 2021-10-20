[![Build Status](https://app.travis-ci.com/kalderman/demo.svg?branch=master)](https://app.travis-ci.com/kalderman/demo)

## Turtle graphics
This demo is an interactive OpenGL implementation of [turtle graphics](https://en.wikipedia.org/wiki/Turtle_graphics).

### About
The primary purpose of this demo (in 2019) was to reintroduce myself to C++.
The secondary purpose was to explore some modern features of C++ and see what the code might look like if I used some concepts from fp.

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

### TODO (probably won't get around to):
- Enable Release/Debug switching.
- Draw a turtle (currently a triangle).
- Stop the turtle at the edge of the window or pass to other side.
- Test some of the drawing/state related code.
- Add ability to change line color.
- Make movement and rotation values configurable.
- Make keys configurable.
- Use modern OpenGL to do the rendering.
- Optimize...
- ... turn this into an asteroids game. :)
