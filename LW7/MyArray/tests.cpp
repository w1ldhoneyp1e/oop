#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "MyArray.h"
#include <string>
#include <vector>

TEST_CASE("constructors")
{
	SECTION("default constructor")
	{
		MyArray<int> arr;
		REQUIRE(arr.GetSize() == 0);
		REQUIRE(arr.GetCapacity() == 0);
		REQUIRE(arr.IsEmpty());
	}

	SECTION("copy constructor")
	{
		MyArray<std::string> original;
		original.PushBack("hello");
		original.PushBack("world");

		MyArray<std::string> copy(original);
		REQUIRE(copy.GetSize() == 2);
		REQUIRE(copy.GetCapacity() >= 2);
		REQUIRE(copy[0] == "hello");
		REQUIRE(copy[1] == "world");

		copy[0] = "hi";
		REQUIRE(original[0] == "hello");
	}
	
	SECTION("move constructor")
	{
		MyArray<int> original;
		original.PushBack(10);
		original.PushBack(20);
		size_t oldCapacity = original.GetCapacity();

		MyArray<int> moved(std::move(original));
		REQUIRE(moved.GetSize() == 2);
		REQUIRE(moved.GetCapacity() == oldCapacity);
		REQUIRE(moved[1] == 20);

		REQUIRE(original.GetSize() == 0);
		REQUIRE(original.GetCapacity() == 0);
		REQUIRE(original.IsEmpty());
	}
}

TEST_CASE("element manipulation")
{
	MyArray<int> arr;
	
	SECTION("push back")
	{
		arr.PushBack(1);
		REQUIRE(arr.GetSize() == 1);
		REQUIRE(arr.GetCapacity() == 1);
		REQUIRE(arr[0] == 1);

		arr.PushBack(2);
		REQUIRE(arr.GetSize() == 2);
		REQUIRE(arr.GetCapacity() == 2);
		
		arr.PushBack(3);
		REQUIRE(arr.GetSize() == 3);
		REQUIRE(arr.GetCapacity() == 4);
	}

	SECTION("index operator")
	{
		arr.PushBack(100);
		arr.PushBack(200);

		REQUIRE(arr[0] == 100);
		arr[1] = 250;
		REQUIRE(arr[1] == 250);

		const MyArray<int>& constArr = arr;
		REQUIRE(constArr[0] == 100);

		REQUIRE_THROWS_AS(arr[2], std::out_of_range);
		REQUIRE_THROWS_AS(constArr[2], std::out_of_range);
	}

	SECTION("resize")
	{
		arr.PushBack(1);
		arr.PushBack(2);
		arr.PushBack(3);

		arr.Resize(5);
		REQUIRE(arr.GetSize() == 5);
		REQUIRE(arr.GetCapacity() >= 5);
		REQUIRE(arr[2] == 3);
		REQUIRE(arr[3] == 0);
		REQUIRE(arr[4] == 0);

		arr.Resize(2);
		REQUIRE(arr.GetSize() == 2);
		REQUIRE(arr[0] == 1);
		REQUIRE(arr[1] == 2);

		REQUIRE_THROWS_AS(arr[2], std::out_of_range);
	}

	SECTION("clear")
	{
		arr.PushBack(10);
		arr.PushBack(20);
		arr.Clear();
		REQUIRE(arr.GetSize() == 0);
		REQUIRE(arr.GetCapacity() == 0);
		REQUIRE(arr.IsEmpty());
	}
}

TEST_CASE("assignment operators")
{
	SECTION("copy assignment")
	{
		MyArray<int> original;
		original.PushBack(1);
		original.PushBack(2);
		
		MyArray<int> assigned;
		assigned.PushBack(99);
		assigned = original;

		REQUIRE(assigned.GetSize() == 2);
		REQUIRE(assigned[1] == 2);

		assigned[0] = 5;
		REQUIRE(original[0] == 1);
	}

	SECTION("move assignment")
	{
		MyArray<std::string> original;
		original.PushBack("a");
		original.PushBack("b");
		size_t oldCapacity = original.GetCapacity();

		MyArray<std::string> moved;
		moved.PushBack("c");
		moved = std::move(original);
		
		REQUIRE(moved.GetSize() == 2);
		REQUIRE(moved.GetCapacity() == oldCapacity);
		REQUIRE(moved[0] == "a");

		REQUIRE(original.GetSize() == 0);
		REQUIRE(original.GetCapacity() == 0);
	}
}

TEST_CASE("iterators")
{
	MyArray<int> arr;
	arr.PushBack(10);
	arr.PushBack(20);
	arr.PushBack(30);

	SECTION("forward iterators")
	{
		int sum = 0;
		for (const auto& val : arr)
		{
			sum += val;
		}
		REQUIRE(sum == 60);

		auto it = arr.begin();
		REQUIRE(*it == 10);
		++it;
		REQUIRE(*it == 20);
		*it = 25;
		REQUIRE(arr[1] == 25);
	}
	
	SECTION("reverse iterators")
	{
		std::vector<int> result;
		for (auto it = arr.rbegin(); it != arr.rend(); ++it)
		{
			result.push_back(*it);
		}
		std::vector<int> expected = {30, 20, 10};
		REQUIRE(result == expected);
	}
}

TEST_CASE("templated assignment")
{
	MyArray<double> doubleArr;
	doubleArr.PushBack(1.1);
	doubleArr.PushBack(2.7);
	doubleArr.PushBack(-3.5);

	MyArray<int> intArr;
	intArr = doubleArr;

	REQUIRE(intArr.GetSize() == 3);
	REQUIRE(intArr[0] == 1);
	REQUIRE(intArr[1] == 2);
	REQUIRE(intArr[2] == -3);
} 