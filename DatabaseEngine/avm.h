#pragma once

// VM instruction set
enum StatementType {
	statement_insert,
	statement_select
};

struct Statement {
	StatementType type;
};
// our VM, it executes byte code compiled from SQL
class Avm {
public:
	void execute_statement(Statement* statement);
};

