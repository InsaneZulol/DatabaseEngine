#pragma once
#include <cstdint>
#include <array>
#include <filesystem>
#include <fstream>

namespace table {
	constexpr auto ROWS_PER_PAGE = 32;
	constexpr auto MAX_PAGES = 100;
	constexpr auto CACHE_MAX_ROWS = MAX_PAGES * ROWS_PER_PAGE;
	using data_page = std::vector<std::string>;

	// The Pager accesses the page cache and the file. The Table object makes requests for pages through the pager.
	struct Pager {

		Pager(std::string filename);
		void db_close();

		std::array<data_page, MAX_PAGES> pages; // page cache
		uint32_t _filelength;
		std::fstream _filestream;
		std::string _filename;
	};
}
