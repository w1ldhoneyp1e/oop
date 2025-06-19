#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "StringList.h"
#include <string>
#include <vector>
#include <algorithm>

TEST_CASE("StringList methods")
{
    StringList list;

    SECTION("New list is empty")
    {
        REQUIRE(list.IsEmpty());
        REQUIRE(list.GetSize() == 0);
    }

    SECTION("PushBack and PushFront")
    {
        std::string hello = "hello";
        list.PushBack(hello);
        list.PushFront("world");
        list.PushBack(std::string("!"));
        REQUIRE(list.GetSize() == 3);

        std::vector<std::string> expected = {"world", "hello", "!"};
        size_t i = 0;
        for (const auto& s : list)
        {
            REQUIRE(s == expected[i++]);
        }
    }

    SECTION("Clear")
    {
        list.PushBack("a");
        list.PushBack("b");
        list.Clear();
        REQUIRE(list.IsEmpty());
        REQUIRE(list.GetSize() == 0);
    }
}

TEST_CASE("Copy and move")
{
    StringList list;
    list.PushBack("a");
    list.PushBack("b");

    SECTION("Copy constructor")
    {
        StringList copy(list);
        REQUIRE(copy.GetSize() == 2);
        REQUIRE(std::equal(copy.begin(), copy.end(), list.begin()));
    }

    SECTION("Copy assignment operator")
    {
        StringList copy;
        copy = list;
        REQUIRE(copy.GetSize() == 2);
        REQUIRE(std::equal(copy.begin(), copy.end(), list.begin()));
    }

    SECTION("Move constructor")
    {
        StringList moved(std::move(list));
        REQUIRE(moved.GetSize() == 2);
        REQUIRE(list.GetSize() == 0);
    }

    SECTION("Move assignment operator")
    {
        StringList tmp;
        tmp.PushBack("x");
        tmp = StringList();
        REQUIRE(tmp.IsEmpty());
    }
}

TEST_CASE("Insert and erase")
{
    StringList list;
    list.PushBack("a");
    list.PushBack("b");
    list.PushBack("c");

    SECTION("Insert, begin(), end(), ++it")
    {
        auto it = list.begin();
        list.Insert(it, "start");
        it = list.begin();
        ++it;
        list.Insert(it, "middle");
        list.Insert(list.end(), "end");

        std::vector<std::string> expected = {"start", "middle", "a", "b", "c", "end"};
        size_t i = 0;
        for (const auto& s : list)
        {
            REQUIRE(s == expected[i++]);
        }
    }

    SECTION("Erase")
    {
        auto it = list.begin();
        list.Erase(it);
        REQUIRE(list.GetSize() == 2);
        REQUIRE(*list.begin() == "b");

        it = list.begin();
        ++it;
        list.Erase(it);
        REQUIRE(list.GetSize() == 1);
        REQUIRE(*list.begin() == "b");

        list.Erase(list.begin());
        REQUIRE(list.IsEmpty());
    }
}

TEST_CASE("StringList: iterators and reverse iterators")
{
    StringList list;
    list.PushBack("1");
    list.PushBack("2");
    list.PushBack("3");

    SECTION("Regular iterators")
    {
        std::vector<std::string> expected = {"1", "2", "3"};
        size_t i = 0;
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            REQUIRE(*it == expected[i++]);
        }
    }

    SECTION("Const iterators")
    {
        const StringList& clist = list;
        std::vector<std::string> expected = {"1", "2", "3"};
        size_t i = 0;
        for (auto it = clist.begin(); it != clist.end(); ++it)
        {
            REQUIRE(*it == expected[i++]);
        }
    }

    SECTION("Range-based for")
    {
        std::vector<std::string> expected = {"1", "2", "3"};
        size_t i = 0;
        for (const auto& s : list)
        {
            REQUIRE(s == expected[i++]);
        }
    }

    SECTION("Reverse iterators")
    {
        std::vector<std::string> expected = {"3", "2", "1"};
        size_t i = 0;
        for (auto it = list.rbegin(); it != list.rend(); ++it)
        {
            REQUIRE(*it == expected[i++]);
        }
    }
}

TEST_CASE("edge cases")
{
    StringList list;

    SECTION("Erase end()")
    {
        REQUIRE(list.Erase(list.end()) == list.end());
        list.Insert(list.begin(), "first");
        REQUIRE(list.GetSize() == 1);
        REQUIRE(*list.begin() == "first");
    }

    SECTION("Self-assignment")
    {
        list.PushBack("a");
        list.PushBack("b");
        list = list;
        REQUIRE(list.GetSize() == 2);
        REQUIRE(*list.begin() == "a");
    }
    
    SECTION("Erasing the only element")
    {
        list.PushBack("single");
        auto it = list.Erase(list.begin());
        REQUIRE(list.IsEmpty());
        REQUIRE(it == list.end());
    }

    SECTION("Clearing an empty list is safe")
    {
        list.Clear();
        REQUIRE(list.IsEmpty());
    }
}

TEST_CASE("iterator operations")
{
    StringList list;
    list.PushBack("abc");
    list.PushBack("def");
    list.PushBack("ghi");

    SECTION("Iterator decrement")
    {
        auto it = list.end();
        --it;
        REQUIRE(*it == "ghi");
        --it;
        REQUIRE(*it == "def");
        --it;
        REQUIRE(*it == "abc");
    }

    SECTION("Arrow operator")
    {
        auto it = list.begin();
        REQUIRE(it->size() == 3);
        REQUIRE(it->at(0) == 'a');
    }

    SECTION("Const reverse iterators")
    {
        const StringList& clist = list;
        std::vector<std::string> expected = {"ghi", "def", "abc"};
        size_t i = 0;
        for (auto it = clist.crbegin(); it != clist.crend(); ++it)
        {
            REQUIRE(*it == expected[i++]);
        }
    }
}
