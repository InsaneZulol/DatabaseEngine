// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "shell_controller.h"
#include "sql_compiler.h"
#include "table_structure.h"

// main starts infinite input await loop.
int main()
{
	try {
		ShellController shell;
		SqlCompiler compiler;
		Avm vm;
		auto table = new table::Table();
		while (true) {
			shell.input_prompt();
			shell.input_get();
			// check if it's a shell command or a ASQL statement.
			if (shell.input.front() == '/') {
				switch(shell.exec_command(shell.input)) {
					case (command_success):
						break;
					case (command_unrecognized):
						std::cout << "Unrecognized command " + shell.input << std::endl;
						continue;
					case (command_shutdown):
						return 0;
				}
			}
			// handle a ASQL statement; first parse the input.
			Statement statement;
			switch (compiler.prepare_statement(shell.input, &statement)) {
			case (prepare_success):
				break;
			case (prepare_syntax_error):
				std::cout << "Syntax error. Could not parse statement." << std::endl;
				continue;
			case (prepare_unrecognized_statement):
				std::cout << "Unrecognized statement at start of " + shell.input << std::endl;
				continue;
			}
			// passing the statement to VM for it to be executed.
			switch (vm.execute_statement(&statement, table)) {
			case(execute_success):
				std::cout << "Executed statement." << std::endl;
				break;
			case(execute_table_full):
				std::cout << "Error. Table full." << std::endl;
				break;
			}
		}
	}
	catch (std::exception& e) {
		std::cout << "exception occured: " << e.what() << std::endl;
	}
}