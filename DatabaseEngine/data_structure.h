#pragma once
#include <cstdint>
#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>

// this is temporary 'fake' table. TODO: replace with b-tree
	// Saving data to DB:
	// 1.	Get new row object from input
	// 2.	Serialize the new row to ascii
	// 3	Save serialized row to Table at the end
	// Each Table consists of pages
	// Each page consists of rows
	// Each row consists of portable ascii data
namespace table
{
	enum MemSaveRowResult {
		memsave_success,
		memsave_error_full
	};

	constexpr auto ROWS_PER_PAGE = 32;
	constexpr auto TABLE_MAX_PAGES = 100;
	constexpr auto TABLE_MAX_ROWS = TABLE_MAX_PAGES * ROWS_PER_PAGE;
	using data_page = std::vector<std::string>;

	struct Table {
		uint32_t num_rows;
		std::array<data_page, TABLE_MAX_PAGES> pages;
		// function to save row in memory
		// Returns true if save was succesful. Returns false if save was unsuccesful,
		// i.e. all pages are full.
		MemSaveRowResult save_row(const std::string& new_row);
	};

	struct TableRow {
		uint32_t id = 0;
		std::string name;
		std::string email;
		// serialize row to portable text-data and then save it data into destination Table
		const std::string serialize_row();
		// deserialize row from portable text-data to C++ object. Returns pointer to table_row.
		TableRow* deserialize_row(const std::string& src_serialized_row);
		
	private:
		friend class boost::serialization::access;

		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version) { 
			ar& id;
			ar& name;
			ar& email;
		}

	};



}
