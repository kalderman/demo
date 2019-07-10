#include "catch.hpp"
#include "turtle.hpp"
#include "turtle_events.hpp"
#include "match.h"
#include "advance_turtle.h"

#include <variant>
#include <iostream>
#include <string>

using namespace std;

TEST_CASE("Default turtle has expected state")
{
    auto given = Turtle();

    REQUIRE( is_pen_up(given) );
    REQUIRE( given.orientation.degrees == 0 );
    REQUIRE( given.position.X == Approx(.0f) );
    REQUIRE( given.position.Y == Approx(.0f) );
}

TEST_CASE("Foward movement advances the turtle 10 units"){
    auto given = Turtle();
    auto event = Move();
    auto actual = advance_turtle(given, event);
    auto expected = Move::Distance;
    REQUIRE( actual.position.Y == Approx(expected) );
}

TEST_CASE("Turn clockwise rotates the turtle 10 degrees clockwise"){
    auto given = Turtle();
    auto event = Rotate(Rotate::Clockwise());
    auto actual = advance_turtle(given, event);
    auto expected = Rotate::Degrees;
    REQUIRE( actual.orientation.degrees == expected );
}

TEST_CASE("Turn counterclockwise rotates the turtle 10 degrees counterclockwise"){
    auto given = Turtle();
    auto event = Rotate(Rotate::Counterclockwise());
    auto actual = advance_turtle(given, event);
    auto expected = -Rotate::Degrees;
    REQUIRE( actual.orientation.degrees == expected );
}

TEST_CASE("Toggle pen from default sets pen to down"){
    auto given = Turtle();
    auto event = TogglePen{};
    auto actual = advance_turtle(given, event);
    REQUIRE( is_pen_down(actual) );
}

Turtle rotate_90cw(const Turtle& t){
    auto rotate = Rotate(Rotate::Clockwise());
    auto t1 = advance_turtle(t, rotate);
    auto t2 = advance_turtle(t1, rotate);
    auto t3 = advance_turtle(t2, rotate);
    auto t4 = advance_turtle(t3, rotate);
    auto t5 = advance_turtle(t4, rotate);
    auto t6 = advance_turtle(t5, rotate);
    auto t7 = advance_turtle(t6, rotate);
    auto t8 = advance_turtle(t7, rotate);
    return advance_turtle(t8, rotate);
}

TEST_CASE("Draw a 10x10 square"){
    auto given = Turtle();

    auto pen_down = advance_turtle(given, TogglePen());
    REQUIRE( is_pen_down(pen_down) );
    REQUIRE( pen_down.position.X == Approx(.0f) );
    REQUIRE( pen_down.position.Y == Approx(.0f) );

    auto move = Move();
    auto top_left = advance_turtle(pen_down, move);
    CHECK( is_pen_down(top_left) );
    REQUIRE( top_left.position.X == Approx(.0f) );
    REQUIRE( top_left.position.Y == Approx(10.0f) );
    
    auto top_left_rotated_90 = rotate_90cw(top_left);
    auto top_right = advance_turtle(top_left_rotated_90, move);
    CHECK( is_pen_down(top_right) );
    REQUIRE( top_right.position.X == Approx(10.0f) );
    REQUIRE( top_right.position.Y == Approx(10.0f) );

    auto top_right_rotated_180 = rotate_90cw(top_right);
    auto bottom_right = advance_turtle(top_right_rotated_180, move);
    CHECK( is_pen_down(bottom_right) );
    REQUIRE( bottom_right.position.X == Approx(10.0f) );
    REQUIRE( bottom_right.position.Y == Approx(.0f) );

    auto bottom_right_rotated_270 = rotate_90cw(bottom_right);
    auto bottom_left = advance_turtle(bottom_right_rotated_270, move);
    CHECK( is_pen_down(bottom_left) );
    REQUIRE( bottom_left.position.X == Approx(.0f) );
    REQUIRE( bottom_left.position.Y == Approx(.0f).margin(0.001f) );
}