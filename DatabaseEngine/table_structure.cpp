#include "table_structure.h"

namespace table
{

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

	void serialize_row(table_row* new_row, Table* table) {
		std::stringstream ss; // napewno tutaj?

		boost::archive::text_oarchive oa(ss);
		oa << new_row;
		const std::string serialized_row = ss.str(); // this is the new serialized row.
		// save in memory. todo: MOVE IT OUT OF THIS?.
		bool res = save_row(table, serialized_row);
	}
	// takes in serialized data(string), spits out C++ row object
	void deserialize_row(std::string serialized_row, table_row* destination) {
		std::stringstream ss; // napewno tutaj?

		boost::archive::text_iarchive ia(ss); // to error :( przenieœ ss poza funkcjê
		ss << serialized_row;
		ia >> destination;
	}

	void print_row(table_row* row) {
		printf("(%d, %s, %s)\n", row->id, row->name, row->email);
	}
}