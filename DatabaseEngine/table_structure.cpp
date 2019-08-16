#include "table_structure.h"

namespace table
{
	// encapsulate in Table?
	bool Table::save_row(const std::string& new_row) {
		for (auto page = this->pages.begin(); page != this->pages.end(); ++page) {
			const size_t this_page_size = page->size() * sizeof(data_page);
			const size_t free_space = MAX_PAGE_SIZE - this_page_size;

			if (free_space >= new_row.size()) {
				page->push_back(new_row);
				return true;
			}
			// if we are at last page check if we can fit here. If not, then return false.
			if (page == this->pages.end() - 1) {
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