#pragma once
#include <string>
#include <iostream>

enum CommandResult {
	command_success,
	command_shutdown,
	command_unrecognized
};

class ShellController {
public:
	std::string input;
	// reads statement/command from users console input
	void input_get();
	// 'draws' input symbol for the user
	void input_prompt();

	CommandResult exec_command(std::string& input_buffer);
};
