#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "MyString.h"
#include <iostream>
#include <sstream>
#include <vector>

TEST_CASE("Constructors")
{
    SECTION("Default")
    {
        MyString s1;
        REQUIRE(s1.GetLength() == 0);
        REQUIRE(s1.GetCapacity() == 0);
    }

    SECTION("From C-string")
    {
        MyString s2("Hello");
        REQUIRE(s2.GetLength() == 5);
        REQUIRE(s2.GetStringData()[0] == 'H');
        REQUIRE(s2.GetStringData()[4] == 'o');
        REQUIRE(s2.GetStringData()[5] == '\0');
    }

    SECTION("From C-string with length")
    {
        const char* str = "Hello, world!";
        MyString s3(str, 5);
        REQUIRE(s3.GetLength() == 5);
        REQUIRE(s3.GetStringData()[0] == 'H');
        REQUIRE(s3.GetStringData()[4] == 'o');
        REQUIRE(s3.GetStringData()[5] == '\0');
    }

    SECTION("Copy constructor")
    {
        MyString original("Hello");
        MyString s4(original);
        REQUIRE(s4.GetLength() == 5);
        REQUIRE(s4.GetStringData()[0] == 'H');
        REQUIRE(s4.GetStringData()[4] == 'o');
        REQUIRE(s4.GetStringData()[5] == '\0');
        REQUIRE(s4 == original);
    }

    SECTION("From std::string")
    {
        std::string stlStr = "STL string";
        MyString s5(stlStr);
        REQUIRE(s5.GetLength() == 10);
        REQUIRE(s5.GetStringData()[0] == 'S');
        REQUIRE(s5.GetStringData()[9] == 'g');
        REQUIRE(s5.GetStringData()[10] == '\0');
    }

    SECTION("String with embedded nulls")
    {
        char data[] = {'A', 'B', '\0', 'C', 'D', '\0'};
        MyString s6(data, 6);
        REQUIRE(s6.GetLength() == 6);
        REQUIRE(s6.GetStringData()[0] == 'A');
        REQUIRE(s6.GetStringData()[2] == '\0');
        REQUIRE(s6.GetStringData()[3] == 'C');
        REQUIRE(s6.GetStringData()[5] == '\0');
        REQUIRE(s6.GetStringData()[6] == '\0');
    }

    SECTION("Move constructor")
    {
        MyString s7("Move constructor test");
        MyString s8(std::move(s7));
        REQUIRE(s8.GetLength() == 21);
        REQUIRE(s8.GetStringData()[0] == 'M');
        REQUIRE(s8.GetStringData()[20] == 't');
        REQUIRE(s7.GetLength() == 0);
        REQUIRE(s7.GetCapacity() == 0);
        REQUIRE(s7.GetStringData()[0] == '\0');
    }
}

TEST_CASE("Basic functions")
{
    SECTION("GetLength")
    {
        MyString s1("blabla");
        REQUIRE(s1.GetLength() == 6);
    }

    SECTION("GetStringData")
    {
        MyString s1("blabla");
        REQUIRE(s1.GetStringData()[0] == 'b');
        REQUIRE(s1.GetStringData()[2] == 'a');
        REQUIRE(s1.GetStringData()[6] == '\0');
    }

    SECTION("SubString")
    {
        MyString s1("Test string");
        MyString s2 = s1.SubString(5, 3);
        REQUIRE(s2.GetLength() == 3);
        REQUIRE(s2.GetStringData()[0] == 's');
        REQUIRE(s2.GetStringData()[2] == 'r');

        MyString s3 = s1.SubString(8, 10);
        REQUIRE(s3.GetLength() == 3);
        REQUIRE(s3.GetStringData()[0] == 'i');
        REQUIRE(s3.GetStringData()[2] == 'g');
    }

    SECTION("Clear")
    {
        MyString s1("Test string");
        s1.Clear();
        REQUIRE(s1.GetLength() == 0);
        REQUIRE(s1.GetCapacity() == 0);
        REQUIRE(s1.GetStringData()[0] == '\0');
    }
}

TEST_CASE("Assignment")
{
    SECTION("Copy assignment")
    {
        MyString s1("Original");
        MyString s2;
        s2 = s1;
        REQUIRE(s2.GetLength() == s1.GetLength());
        REQUIRE(s2 == s1);
    }

    SECTION("Move assignment")
    {
        MyString s1("Original");
        MyString s3;
        s3 = std::move(s1);
        REQUIRE(s3.GetLength() == 8);
        REQUIRE(s3.GetStringData()[0] == 'O');
        REQUIRE(s1.GetLength() == 0);
        REQUIRE(s1.GetCapacity() == 0);
    }

    SECTION("Self-assignment")
    {
        MyString s4("SelfAssignment");
        s4 = s4;
        REQUIRE(s4.GetLength() == 14);
        REQUIRE(s4.GetStringData()[0] == 'S');
        REQUIRE(s4.GetStringData()[13] == 't');
    }
}

TEST_CASE("Concatenation operators")
{
    SECTION("MyString + MyString")
    {
        MyString s1("Hello");
        MyString s2(" World");
        MyString s3 = s1 + s2;
        REQUIRE(s3.GetLength() == 11);
        REQUIRE(s3.GetStringData()[0] == 'H');
        REQUIRE(s3.GetStringData()[5] == ' ');
        REQUIRE(s3.GetStringData()[10] == 'd');
    }

    SECTION("MyString += MyString")
    {
        MyString s4("Append");
        s4 += " this";
        REQUIRE(s4.GetLength() == 11);
        REQUIRE(s4.GetStringData()[0] == 'A');
        REQUIRE(s4.GetStringData()[6] == ' ');
        REQUIRE(s4.GetStringData()[10] == 's');
    }

    SECTION("std::string + MyString")
    {
        std::string stlStr = "STL";
        MyString s1("Hello");
        MyString s5 = stlStr + s1;
        REQUIRE(s5.GetLength() == 8);
        REQUIRE(s5.GetStringData()[0] == 'S');
        REQUIRE(s5.GetStringData()[3] == 'H');
        REQUIRE(s5.GetStringData()[7] == 'o');
    }

    SECTION("const char* + MyString")
    {
        MyString s1("Hello");
        MyString s6 = "C-str" + s1;
        REQUIRE(s6.GetLength() == 10);
        REQUIRE(s6.GetStringData()[0] == 'C');
        REQUIRE(s6.GetStringData()[5] == 'H');
        REQUIRE(s6.GetStringData()[9] == 'o');
    }
}

TEST_CASE("Comparison operators")
{
    MyString s1("aaa");
    MyString s2("aaa");
    MyString s3("bbb");
    MyString s4("aa");

    SECTION("==")
    {
        REQUIRE(s1 == s2);
        REQUIRE_FALSE(s1 == s3);
    }

    SECTION("!=")
    {
        REQUIRE(s1 != s3);
        REQUIRE_FALSE(s1 != s2);
    }

    SECTION("<")
    {
        REQUIRE(s1 < s3);
        REQUIRE_FALSE(s3 < s1);
        REQUIRE_FALSE(s1 < s2);
        REQUIRE(s4 < s1);
    }

    SECTION(">")
    {
        REQUIRE(s3 > s1);
        REQUIRE_FALSE(s1 > s3);
        REQUIRE_FALSE(s1 > s2);
        REQUIRE(s1 > s4);
    }

    SECTION("<=")
    {
        REQUIRE(s1 <= s2);
        REQUIRE(s1 <= s3);
        REQUIRE_FALSE(s3 <= s1);
    }

    SECTION(">=")
    {
        REQUIRE(s1 >= s2);
        REQUIRE(s3 >= s1);
        REQUIRE_FALSE(s1 >= s3);
    }
}

TEST_CASE("Stream operators")
{
    SECTION("Output operator")
    {
        MyString s1("Output test");
        std::ostringstream oss;
        oss << s1;
        REQUIRE(oss.str() == "Output test");
    }

    SECTION("Input operator")
    {
        MyString s2;
        std::istringstream iss("Input test");
        iss >> s2;
        REQUIRE(s2.GetLength() == 5);
        REQUIRE(s2.GetStringData()[0] == 'I');
        REQUIRE(s2.GetStringData()[4] == 't');
    }

    SECTION("Output string with embedded nulls")
    {
        char data[] = {'A', 'B', '\0', 'C', 'D'};
        MyString s3(data, 5);
        std::ostringstream oss2;
        oss2 << s3;
        std::string result = oss2.str();
        REQUIRE(result.length() == 5);
        REQUIRE(result[0] == 'A');
        REQUIRE(result[2] == '\0');
        REQUIRE(result[4] == 'D');
    }
}

TEST_CASE("Capacity management")
{
    SECTION("Initial")
    {
        MyString s1("Initial");
        REQUIRE(s1.GetLength() == 7);
        REQUIRE(s1.GetCapacity() == 8);
    }

    SECTION("Capacity increase after append")
    {
        MyString s1("Initial");
        s1 += " text";
        REQUIRE(s1.GetLength() == 12);
        REQUIRE(s1.GetCapacity() >= 13);
    }

    SECTION("Capacity after clear")
    {
        MyString s1("Initial text");
        s1.Clear();
        REQUIRE(s1.GetCapacity() == 0);
    }
}
