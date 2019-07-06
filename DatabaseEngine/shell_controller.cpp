#include <iostream>
#include "shell_controller.h"

void ShellController::input_get() {
	std::getline(std::cin, this->input);
}

void ShellController::input_prompt() {
	std::cout << " > ";
}

CommandResult ShellController::exec_command(std::string& input_buffer) {
	if(input_buffer == "/quit") {
		std::cout << "[shutting down...]" << std::endl;
		return command_shutdown;
	}
	else {
		return command_unrecognized;
	}
}
