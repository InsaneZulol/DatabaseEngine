// .cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "user_interface.h"

// main starts infinite input await loop.
int main()
{
	try {
		user_interface shell;
		while (true) {
			shell.input_prompt();
			shell.input_get();
			if (shell.input == "/quit") {
				std::cout << "[shutting down...]" << std::endl;
				return 0;
			}
			else {
				std::cout << "Unknown command: " + shell.input << std::endl;
			}
		}
	}
	catch (...) {
		std::cout << "unknown exception occured"  << std::endl;
	}
}