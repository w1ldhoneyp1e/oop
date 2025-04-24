#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <sstream>
#include <iostream>
#include "Car.h"
#include "RemoteControl.h"

TEST_CASE("Car initialization")
{
    Car car;
    REQUIRE(car.IsEngineOn() == false);
    REQUIRE(car.GetSpeed() == 0);
    REQUIRE(car.GetGear() == Car::Gear::Neutral);
    REQUIRE(car.GetDirection() == Car::Direction::Stop);
}

TEST_CASE("Car engine operations")
{
    Car car;

    SECTION("Can turn on engine")
    {
        REQUIRE_NOTHROW(car.TurnOnEngine());
        REQUIRE(car.IsEngineOn());
    }

    SECTION("Cannot turn on engine twice")
    {
        car.TurnOnEngine();
        REQUIRE_THROWS_WITH(car.TurnOnEngine(), "Car is already started");
    }

    SECTION("Cannot turn off non-started engine")
    {
        REQUIRE_THROWS_WITH(car.TurnOffEngine(), "Car is not started");
    }

    SECTION("Can turn off engine in neutral gear with zero speed")
    {
        car.TurnOnEngine();
        REQUIRE_NOTHROW(car.TurnOffEngine());
        REQUIRE_FALSE(car.IsEngineOn());
    }

    SECTION("Cannot turn off engine when moving")
    {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        REQUIRE_THROWS_WITH(car.TurnOffEngine(), "Car cannot be turned off while moving");
    }
}

TEST_CASE("Car gear operations")
{
    Car car;
    car.TurnOnEngine();

    SECTION("Cannot set gear when engine is off")
    {
        Car car2;
        REQUIRE_THROWS_WITH(car2.SetGear(1), "Cannot set gear while engine is off");
    }

    SECTION("Can set first gear from neutral")
    {
        REQUIRE_NOTHROW(car.SetGear(1));
        REQUIRE(car.GetGear() == Car::Gear::First);
    }

    SECTION("Can set reverse gear only when stopped")
    {
        REQUIRE_NOTHROW(car.SetGear(-1));
        car.SetSpeed(10);
        REQUIRE_THROWS_WITH(car.SetGear(-1), "Cannot reverse while moving");
    }

    SECTION("Cannot set invalid gear")
    {
        REQUIRE_THROWS_WITH(car.SetGear(-2), "Invalid gear");
        REQUIRE_THROWS_WITH(car.SetGear(6), "Invalid gear");
    }
}

TEST_CASE("Car speed operations")
{
    Car car;
    car.TurnOnEngine();

    SECTION("Cannot set speed when engine is off")
    {
        Car car2;
        REQUIRE_THROWS_WITH(car2.SetSpeed(10), "Cannot set speed while engine is off");
    }

    SECTION("Cannot increase speed in neutral")
    {
        REQUIRE_THROWS_WITH(car.SetSpeed(10), "Cannot accelerate on neutral");
    }

    SECTION("Can set valid speed for first gear")
    {
        car.SetGear(1);
        REQUIRE_NOTHROW(car.SetSpeed(20));
        REQUIRE(car.GetSpeed() == 20);
        REQUIRE(car.GetDirection() == Car::Direction::Forward);
    }

    SECTION("All speed limits") // vse sluchai
    {
        SECTION("Reverse gear")
        {
            car.SetGear(-1);

            REQUIRE_NOTHROW(car.SetSpeed(0));
            REQUIRE_NOTHROW(car.SetSpeed(20));

            REQUIRE_THROWS_WITH(car.SetSpeed(21), "Speed is out of gear range");
        }

        SECTION("First gear")
        {
            car.SetGear(1);

            REQUIRE_NOTHROW(car.SetSpeed(0));
            REQUIRE_NOTHROW(car.SetSpeed(30));

            REQUIRE_THROWS_WITH(car.SetSpeed(31), "Speed is out of gear range");
        }

        SECTION("Second gear")
        {
            car.SetGear(1);
            car.SetSpeed(20);
            car.SetGear(2);

            REQUIRE_NOTHROW(car.SetSpeed(20));
            REQUIRE_NOTHROW(car.SetSpeed(50));

            REQUIRE_THROWS_WITH(car.SetSpeed(19), "Speed is out of gear range");
            REQUIRE_THROWS_WITH(car.SetSpeed(51), "Speed is out of gear range");
        }

        SECTION("Third gear")
        {
            car.SetGear(1);
            car.SetSpeed(30);
            car.SetGear(3);

            REQUIRE_NOTHROW(car.SetSpeed(30));
            REQUIRE_NOTHROW(car.SetSpeed(60));

            REQUIRE_THROWS_WITH(car.SetSpeed(29), "Speed is out of gear range");
            REQUIRE_THROWS_WITH(car.SetSpeed(61), "Speed is out of gear range");
        }

        SECTION("Fourth gear")
        {
            car.SetGear(1);
            car.SetSpeed(30);
            car.SetGear(3);
            car.SetSpeed(40);
            car.SetGear(4);

            REQUIRE_NOTHROW(car.SetSpeed(40));
            REQUIRE_NOTHROW(car.SetSpeed(90));

            REQUIRE_THROWS_WITH(car.SetSpeed(39), "Speed is out of gear range");
            REQUIRE_THROWS_WITH(car.SetSpeed(91), "Speed is out of gear range");
        }

        SECTION("Fifth gear")
        {
            car.SetGear(1);
            car.SetSpeed(30);
            car.SetGear(3);
            car.SetSpeed(50);
            car.SetGear(5);

            REQUIRE_NOTHROW(car.SetSpeed(50));
            REQUIRE_NOTHROW(car.SetSpeed(150));

            REQUIRE_THROWS_WITH(car.SetSpeed(49), "Speed is out of gear range");
            REQUIRE_THROWS_WITH(car.SetSpeed(151), "Speed is out of gear range");
        }
    }

    SECTION("Cannot set negative speed")
    {
        car.SetGear(1);
        REQUIRE_THROWS_WITH(car.SetSpeed(-10), "Speed cannot be negative");
    }

    SECTION("Direction changes correctly")
    {
        car.SetGear(-1);
        car.SetSpeed(10);
        REQUIRE(car.GetDirection() == Car::Direction::Backward);

        car.SetSpeed(0);
        REQUIRE(car.GetDirection() == Car::Direction::Stop);

        car.SetGear(1);
        car.SetSpeed(10);
        REQUIRE(car.GetDirection() == Car::Direction::Forward);
    }
}

TEST_CASE("RemoteControl command handling")
{
    Car car;
    std::stringstream input;
    std::stringstream output;
    RemoteControl remote(car, input, output);

    SECTION("Info command")
    {
        input.str("Info\n");
        remote.HandleCommand();
        std::string result = output.str();
        REQUIRE(result.find("Engine is off") != std::string::npos);
        REQUIRE(result.find("Gear: Neutral") != std::string::npos);
        REQUIRE(result.find("Speed: 0") != std::string::npos);
    }

    SECTION("EngineOn command")
    {
        input.str("EngineOn\n");
        remote.HandleCommand();
        REQUIRE(car.IsEngineOn());
    }

    SECTION("SetGear command validation")
    {
        input.str("EngineOn\n");
        remote.HandleCommand();
        output.str("");

        SECTION("Valid gear")
        {
            input.str("SetGear 1\n");
            remote.HandleCommand();
            REQUIRE(car.GetGear() == Car::Gear::First);
        }

        SECTION("Invalid gear format")
        {
            input.str("SetGear 1.5\n");
            remote.HandleCommand();
            REQUIRE(output.str().find("Invalid command argument") != std::string::npos);
        }

        SECTION("Out of range gear")
        {
            input.str("SetGear 6\n");
            remote.HandleCommand();
            REQUIRE(output.str().find("Invalid gear") != std::string::npos);
        }
    }

    SECTION("Command with unexpected arguments")
    {
        input.str("Info 123\n");
        remote.HandleCommand();
        REQUIRE(output.str().find("Invalid command argument") != std::string::npos);
    }

    SECTION("Unknown command")
    {
        input.str("UnknownCommand\n");
        remote.HandleCommand();
        REQUIRE(output.str().find("Unknown command") != std::string::npos);
    }
}
