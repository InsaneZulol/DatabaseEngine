#include "data_structure.h"
#include <iostream>

namespace table
{
	// on each page i will let it allocate max of 32 rows each approx. 100bytes in size = 3200B
	// so each page should be of size 3200+sizeof(page)?
	// i should try to get it to round 4096B so windows can move them in complete pages but fuck it for now
	MemSaveRowResult Table::save_row(const std::string& new_row) {
		for (auto page = this->pages.begin(); page != this->pages.end(); ++page) {
			// if there is enough space then save row on this page
			if (page->size() < ROWS_PER_PAGE) {
				page->push_back(new_row);
				return memsave_success;
			}
		}
	}

	const std::string TableRow::serialize_row() {
		std::stringstream ss;
		boost::archive::text_oarchive oa(ss);
		oa << this;
		const std::string serialized_row = ss.str();
		return serialized_row;
	}

	TableRow* TableRow::deserialize_row(const std::string& src_serialized_row) {
		std::stringstream ss(src_serialized_row);
		boost::archive::text_iarchive ia(ss);
		TableRow* row;
		// operator >> causes change of memory address
		ia >> row;
		return row;
	}

}