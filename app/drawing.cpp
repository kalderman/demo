#include "position.hpp"
#include "drawing.hpp"
#include <glbinding/gl/gl.h>
#include <algorithm>

using namespace gl;

void wipe_canvas(){
    glMatrixMode(GL_PROJECTION);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); 
    glOrtho(-1000, 1000, -1000, 1000, 0, 1);
}

unique_ptr<vector<vector<Position>>> get_line_strips(const vector<Turtle>& turtle_log){
    vector<vector<Position>> line_strips;
    auto last_pen_state = false;
    for_each(turtle_log.begin(), turtle_log.end(), [&](const Turtle& t){
        auto pen_state = is_pen_down(t);
        if(!last_pen_state && pen_state){
            line_strips.push_back(vector<Position> { t.position }); //create new line strip and add vertex
        }
        else if(last_pen_state && pen_state){
            auto previous = line_strips.back().back();
            if(previous.X != t.position.X || previous.Y != t.position.Y){
                line_strips.back().push_back(t.position); //add vertex
            }
        }
        last_pen_state = pen_state;
    });

    return make_unique<vector<vector<Position>>>(line_strips);
}

void draw_line_strips(const vector<vector<Position>>& line_strips){
    for_each(line_strips.begin(), line_strips.end(), [](const vector<Position>& line){
        glBegin(GL_LINE_STRIP);
            glColor3f(1.f, 0.f, 0.f);
            for_each(line.begin(), line.end(), [](const Position& v){
                glVertex3f(v.X, v.Y, 0.f);
            });
        glEnd();
    });
}

void draw_triangle(float r, float g, float b){
    glBegin(GL_TRIANGLES);
        glColor3f(r, g, b);
        glVertex3f(-1.0f, -1.0f, .0f);
        glVertex3f(1.0f, -1.0f, .0f);
        glVertex3f(.0f, 1.0f, .0f);
    glEnd();
}

void draw_turtle(const Turtle& t){
    auto angle = t.orientation.degrees;
    auto position = t.position;

    glTranslatef(position.X, position.Y, 0.f);
    glPushMatrix();
        glRotatef(angle, 0.f, 0.f, -1.f);

        glPushMatrix();
            glScalef(20.f, 20.f, 1.f);
            draw_triangle(1.f, 1.f, 1.f);
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0.f, 10.f, 0.f);
            glScalef(10.f, 10.f, 1.f);
            draw_triangle(1.f, 0.f, 0.f);
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

void update_canvas(const vector<Turtle>& turtle_log){
    wipe_canvas();
    draw_line_strips(*get_line_strips(turtle_log));
    draw_turtle(turtle_log.back());
    glFlush();
}
