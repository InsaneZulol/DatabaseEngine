#include "user_interface.h"
#include <iostream>

void user_interface::input_get() {
	std::getline(std::cin, this->input);
}

void user_interface::input_prompt() {
	std::cout << " > ";
}
