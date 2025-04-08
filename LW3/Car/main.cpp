#include <iostream>
#include <windows.h>
#include "Car.h"
#include "RemoteControl.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RU");

	Car car;
	RemoteControl remoteControl(car, std::cin, std::cout);

	while (true)
	{
		std::cout << ">";
		remoteControl.HandleCommand();
	}

	return EXIT_SUCCESS;
}