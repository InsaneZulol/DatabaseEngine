#include "table_structure.h"
#include <iostream>

namespace table
{

	// encapsulate in Table?
	bool save_row(Table* table, const std::string& new_row) {
		for (auto page = table->pages.begin(); page != table->pages.end(); ++page) {
			const size_t this_page_size = page->size() * sizeof(data_page);
			const size_t free_space = MAX_PAGE_SIZE - this_page_size;

			if (free_space >= new_row.size()) {
				page->push_back(new_row);
				return true;
			}
			// if we are at last page check if we can fit here. If not, then return false.
			if (page == table->pages.end() - 1) {
				if (free_space >= new_row.size()) {
					page->push_back(new_row);
					return true;
				}
				else {
					return false;
				}
			}
		}
	}

	const std::string table_row::serialize_row() {
		std::stringstream ss; // napewno tutaj?
		boost::archive::text_oarchive oa(ss);
		oa << this;
		const std::string serialized_row = ss.str();
		return serialized_row;
	}

	const table_row* table_row::deserialize_row(std::string src_serialized_row) {
		std::stringstream ss(src_serialized_row);
		boost::archive::text_iarchive ia(ss);
		ia >> *this;
		return this;
	}

	void print_row(table_row* row) {
		printf("(%d, %s, %s)\n", row->id, row->name, row->email);
	}
}