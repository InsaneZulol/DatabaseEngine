#include <iostream>
#include "avm.h"

ExecuteResult Avm::execute_insert(Statement* statement, table::Table* table) {
	if (table->num_rows >= table::CACHE_MAX_ROWS) { // arbitrary number
		return execute_table_full;
	}
	table::TableRow* row_to_insert = &(statement->new_row_to_insert);
	const std::string serialized_row_to_insert = row_to_insert->serialize_row();

	table::CacheRowResult cache_result = table->cache_row(serialized_row_to_insert);
	if (cache_result == table::CacheRowResult::memsave_success) {
		table->num_rows += 1;
		return execute_success;
	}
	else {
		return execute_table_full;
	}
}

ExecuteResult Avm::execute_select(Statement* statement, table::Table* table) {
	table::TableRow * row = nullptr;
	// iterate over all pages and print each row of each page
	for (auto const& page : table->pager->pages) {
		// now iterate over each row
		for (auto const& row_iter : page) {
			row = row->deserialize_row(row_iter);
			std::cout << '(' << row->id << ", " << row->name << ", " << row->email << ')' << std::endl;
		}
	}
	return execute_success;
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
