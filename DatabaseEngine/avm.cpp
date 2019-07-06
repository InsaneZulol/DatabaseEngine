#include <iostream>
#include "avm.h"

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
