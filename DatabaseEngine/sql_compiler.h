#pragma once
#include <string>

enum StatementType {
	statement_insert,
	statement_select
};

struct Statement {
	StatementType type;
};

enum PrepareResult {
	prepare_success,
	prepare_unrecognized_statement
};

class SqlCompiler {
public:
	PrepareResult prepare_statement(std::string& input_buffer, Statement* statement);

	~SqlCompiler();
};

