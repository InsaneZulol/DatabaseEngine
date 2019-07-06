#include <string>
#include "sql_compiler.h"
#include <iostream>

// This class is responsible for converting SQL text
// from users console input into byte code,
// which is to be further executed by VM.

// SQL to byte code 'compiler'.
PrepareResult SqlCompiler::prepare_statement(std::string& input_buffer, Statement* statement) {
	if(input_buffer.compare(0, 6, "insert") == 0) {
		statement->type = statement_insert;
		return prepare_success;
	}
	if(input_buffer == "select") {
		statement->type = statement_select;
		return prepare_success;
	}

	return prepare_unrecognized_statement;
}
