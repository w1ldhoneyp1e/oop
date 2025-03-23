#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "../LW2/LW2.1/tests.cpp"
#include "../LW2/LW2.1/LW2.1_functions.cpp"

int main(int argc, char* argv[])
{
	return Catch::Session().run(argc, argv);
}