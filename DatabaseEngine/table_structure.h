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

	constexpr auto TABLE_MAX_PAGES = 100;
	constexpr auto MAX_PAGE_SIZE = 4096;
	using data_page = std::vector<std::string>;

	struct Table {
		uint32_t num_rows;
		// fixed-size array of pages
		std::array<data_page, TABLE_MAX_PAGES> pages;
	};
	struct table_row {
		uint32_t id = 0;
		std::string name;
		std::string email;
		// serialize row to portable text-data and then save it data into destination Table
		const std::string serialize_row();
		// deserialize row from portable text-data to C++ object. Returns pointer to table_row.
		const table_row* deserialize_row(std::string serialized_row);
	private:
		friend class boost::serialization::access;

		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version) { 
			ar& id;
			ar& name;
			ar& email;
		}

	};


	// function to save row in memory
	// Returns true if save was succesful. Returns false if save was unsuccesful,
	// i.e. all pages are full.
	bool save_row(Table* table, const std::string& new_row);
	// takes in serialized data(string), spits out C++ row object
	void print_row(table_row* row);
}
