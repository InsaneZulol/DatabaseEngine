// .cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

// 'draws' input symbol for the user
inline void input_prompt() { std::cout << " > "; }
inline void read_input(std::string &input_buf) {
	std::getline(std::cin, input_buf);
}
// main starts infinite input await loop.
int main()
{
	try {
		std::string input;
		while (true) {
			input_prompt();
			read_input(input);
			if (input == "/quit") {
				std::cout << "[shutting down...]" << std::endl;
				return 0;
			}
			else {
				std::cout << "Unknown command: " + input << std::endl;
			}
		}
	}
	catch (...) {
		std::cout << "unknown exception occured"  << std::endl;
	}
}