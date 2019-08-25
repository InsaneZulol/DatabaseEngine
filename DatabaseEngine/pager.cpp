#include <iostream>
#include "pager.h"

namespace fs = std::experimental::filesystem;

// todo: rename 'table' to 'backend'
namespace table {
	Pager::Pager(std::string filename) : _filename(filename), _filelength(0) {
		if (fs::exists(filename)) {
			fs::path p{ filename };
			_filelength = fs::file_size(p);
		}
	}

	// save cache to file:
	//	flushes the page cache to disk
	void Pager::db_close() {

		_filestream.open(_filename, std::ios::out);
		if (_filestream.good()) {
			// iterate over all pages
			for (auto const& page : pages) {
				// iterate over each row of page
				for (auto const& row_iter : page) {
					_filestream << row_iter + ";";
				}
			}
			_filestream.close();
		}
		else std::cout << "Failed to open file" << std::endl;
	}
}