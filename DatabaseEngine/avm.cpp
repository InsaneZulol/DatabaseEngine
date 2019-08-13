#include <iostream>
#include "avm.h"

ExecuteResult Avm::execute_insert(Statement* statement, table::Table* table) {
	if (table->num_rows >= 2000) { // arbitrary magic number
		return EXECUTE_TABLE_FULL;
	}
	table::table_row* row_to_insert = &(statement->new_row_to_insert);

	// save to compact representation in memory
	serialize_row(row_to_insert, table);
	table->num_rows += 1;
	
	return EXECUTE_SUCCESS;
}

ExecuteResult Avm::execute_select(Statement* statement, table::Table* table) {
	table::table_row row;
	// iterate over all pages and print each row of each page
	for (auto const& page : table->pages) {
		// now iterate over each row
		for (auto const& row_iter : page) {
			deserialize_row(row_iter, &row);
			print_row(&row);
		}
	}
	return EXECUTE_SUCCESS;
}

ExecuteResult Avm::execute_statement(Statement* statement, table::Table* table) {
	switch(statement->type) {
		case (statement_insert):
			std::cout << "Doing insert" << std::endl;
			return execute_insert(statement, table);
		case (statement_select):
			std::cout << "Doing select" << std::endl;
			return execute_select(statement, table);
	}
}
