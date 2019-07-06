#pragma once
#include <string>
#include <iostream>

class user_interface {
public:
	// reads statement/command from users console input
	void input_get();
	// 'draws' input symbol for the user
	void input_prompt();
	std::string input;
};
