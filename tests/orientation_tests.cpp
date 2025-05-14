#include <memory>
#include <catch2/catch_test_macros.hpp>
#include "orientation.hpp"
#include "turtle_events.hpp"
#include "match.hpp"

TEST_CASE("Default angle is zero"){
    auto sut = Orientation();
    REQUIRE( sut.degrees == 0 );
}

TEST_CASE("Orientation with clockwise rotation has angle of 10 degrees"){
    auto sut = Orientation(Rotate(Rotate::Clockwise()));
    REQUIRE( sut.degrees == 10 );
}

TEST_CASE("Orientation with counterclockwise rotation has angle of 350 degrees"){
    auto sut = Orientation(Rotate(Rotate::Counterclockwise()));
    REQUIRE( sut.degrees == -10 );
}

TEST_CASE("apply does not change degrees"){
    auto sut = Orientation();
    sut.apply(Rotate(Rotate::Clockwise()));
    REQUIRE( sut.degrees == 0 );
}

TEST_CASE("apply clockwise rotation to default Orientation has angle of 10 degrees"){
    auto sut = Orientation();
    auto actual = sut.apply(Rotate(Rotate::Clockwise()));
    REQUIRE( actual.degrees == 10 );
}

TEST_CASE("apply counterclockwise rotation to default Orientation has angle of -10 degrees"){
    auto sut = Orientation();
    auto actual = sut.apply(Rotate(Rotate::Counterclockwise()));
    REQUIRE( actual.degrees == -10 );
}

void test_360_rotation(Rotate rotation, Orientation sut = Orientation(), int i = 0){
    if (i < 35) {
        auto result = sut.apply(rotation); 
        test_360_rotation(rotation, result, ++i);
    } else {
        auto expected_degrees = visit(match {
                [](const Rotate::Clockwise& _) { return 350; },
                [](const Rotate::Counterclockwise& _){ return -350; }
            },
            rotation.direction);
        CHECK( sut.degrees == expected_degrees );
        auto actual = sut.apply(rotation);
        REQUIRE( actual.degrees == 0 );
    }
}

TEST_CASE("clockwise rotation to 360 returns to 0"){
    test_360_rotation(Rotate(Rotate::Clockwise()));
}

TEST_CASE("counterclockwise rotation to -360 returns to 0"){
    test_360_rotation(Rotate(Rotate::Counterclockwise()));
}