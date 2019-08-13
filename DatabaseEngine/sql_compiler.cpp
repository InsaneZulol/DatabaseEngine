#include <string>
#include <iostream>
#include "sql_compiler.h"
#include "parser.h"

// This class is responsible for converting SQL text
// from users console input into byte code,
// which is to be later then executed by VM.
using boost::spirit::ascii::space;
// SQL to byte code 'compiler'.
PrepareResult SqlCompiler::prepare_statement(std::string& input_buffer, Statement* statement) {
	if(input_buffer.compare(0, 6, "insert") == 0) {
		statement->type = statement_insert;
		// parse
		typedef parser::insert_grammar<std::string::const_iterator> insert_parser;
		const insert_parser g; // Our grammar
		const std::string::const_iterator b = input_buffer.begin();
		const std::string::const_iterator e = input_buffer.end();
		const auto r = phrase_parse(b, e, g, space, statement->new_row_to_insert);
		if(!r) {
			std::cout << "parse failed..." << std::endl;
			return prepare_syntax_error;
		}
		return prepare_success;
	}
	if(input_buffer == "select") {
		statement->type = statement_select;
		return prepare_success;
	}

	return prepare_unrecognized_statement;
}
