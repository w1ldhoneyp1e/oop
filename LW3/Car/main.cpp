#include <iostream>

int main()
{
	Car car;
	RemoteControl remoteControl(car, std::cin, std::cout);

	try
	{
		while (true)
		{
			remoteControl.HandleCommand();
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}