#include "data_structure.h"
#include <iostream>

namespace table
{
	Table::Table(std::string filename) : num_rows(0), pager(std::make_unique<Pager>(filename)) {
		// lets check the file and if it's not empty, load its content to cache
		if (pager->_filelength > 0) {
			pager->_filestream.open(pager->_filename, std::ios::in);
			if (pager->_filestream.good()) {
				std::string line;
				while (std::getline(pager->_filestream, line, ';'))
				{
					CacheRowResult cache_result = cache_row(line);
					if (cache_result == table::CacheRowResult::memsave_success) {
						num_rows += 1;
					}
				}
				pager->_filestream.close();
			}
		}
	}

	// on each page i will let it allocate max of 32 rows each approx. 100bytes in size = 3200B
	// so each page should be of size 3200+sizeof(page) for now?
	CacheRowResult Table::cache_row(const std::string& new_row) {
		auto pbeg = pager->pages.begin(), pend = pager->pages.end();
		for (auto page = pbeg; page != pend; ++page) {
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
		ia >> row;
		return row;
	}

}