// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "shell_controller.h"
#include "sql_compiler.h"


// main starts infinite input await loop.
int main()
{
	try {
		ShellController shell;
		SqlCompiler compiler;
		Avm vm;
		while (true) {
			shell.input_prompt();
			shell.input_get();
			// check if it's a shell command or a ASQL statement.
			if (shell.input.front() == '/') {
				switch(shell.exec_command(shell.input)) {
					case (command_success):
						continue;
					case (command_unrecognized):
						std::cout << "Unrecognized command " + shell.input << std::endl;
						continue;
					case (command_shutdown):
						return 0;
				}
			}
			// here we handle a ASQL statement.
			Statement statement;
			switch (compiler.prepare_statement(shell.input, &statement)) {
			case (prepare_success):
				break;
			case (prepare_unrecognized_statement):
				std::cout << "Unrecognized statement at start of " + shell.input << std::endl;
				continue;
			}
			vm.execute_statement(&statement);
			std::cout << "Executed statement." << std::endl;
		}
	}
	catch (...) {
		std::cout << "unknown exception occured" << std::endl;
	}
}