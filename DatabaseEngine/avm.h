#pragma once
#include "data_structure.h"
// VM instruction set
enum StatementType {
	statement_insert,
	statement_select
};

enum ExecuteResult { 
	execute_success,
	execute_table_full 
};

struct Statement {
	StatementType type;
	table::TableRow new_row_to_insert; // just for insert. The new single row(id, name, email) we will insert into Table.
};

// our VM, it the executes byte code compiled from SQL
class Avm {
public:
	ExecuteResult execute_statement(Statement* statement, table::Table* table);
	ExecuteResult execute_insert(Statement* statement, table::Table* table);
	// select just prints out the content
	ExecuteResult execute_select(Statement* statement, table::Table* table);
};
