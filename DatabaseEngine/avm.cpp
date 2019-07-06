#include <iostream>
#include "avm.h"

// our VM, it executes byte code compiled from SQL
void Avm::execute_statement(Statement* statement) {
	switch(statement->type) {
		case (statement_insert):
			std::cout << "Doing insert" << std::endl;
			break;
		case (statement_select):
			std::cout << "Doing select" << std::endl;
			break;
	}
}
