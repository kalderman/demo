#include <memory>
#include "catch.hpp"
#include "orientation.h"
#include "turtle_events.hpp"

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
    REQUIRE( actual->degrees == 10 );
}

TEST_CASE("apply counterclockwise rotation to default Orientation has angle of -10 degrees"){
    auto sut = Orientation();
    auto actual = sut.apply(Rotate(Rotate::Counterclockwise()));
    REQUIRE( actual->degrees == -10 );
}

TEST_CASE("clockwise rotation to 360 returns to 0"){
    auto sut = std::make_unique<Orientation>(Orientation());
    auto rotation = Rotate(Rotate::Clockwise());
    for(int i = 0; i < 35; ++i)
    {
        sut = sut->apply(rotation); 
    }
    CHECK( sut->degrees == 350 );
    auto actual = sut->apply(rotation);
    REQUIRE( actual->degrees == 0 );
}

TEST_CASE("counterclockwise rotation to -360 returns to 0"){
    auto sut = std::make_unique<Orientation>(Orientation());
    auto rotation = Rotate(Rotate::Counterclockwise());
    for(int i = 0; i < 35; ++i)
    {
        sut = sut->apply(rotation); 
    }
    CHECK( sut->degrees == -350 );
    auto actual = sut->apply(rotation);
    REQUIRE( actual->degrees == 0 );
}