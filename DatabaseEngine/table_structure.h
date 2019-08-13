#pragma once
#include <cstdint>
#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

// this is temporary 'fake' table. TODO: replace with b-tree
namespace table
{
	constexpr auto TABLE_MAX_PAGES = 100;
	constexpr auto MAX_PAGE_SIZE = 4096;

	struct table_row {
		uint32_t id = 0;
		std::string name;
		std::string email;
	private:
		friend class boost::serialization::access;

		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version) { 
			ar& id;
			ar& name;
			ar& email;
		}
	};
	using data_page = std::vector<std::string>;

	struct Table {
		uint32_t num_rows;
		// fixed-size array of pages
		std::array<data_page, TABLE_MAX_PAGES> pages;
	};
	// Saving data to DB:
	// 1.	Serialize a new row
	// 2	Put serialized row to serialized Table at the end(last row)
	// 3. 
			
	// function to save row in memory
	// Returns true if save was succesful. Returns false if save was unsuccesful,
	// i.e. all pages are full.
	bool save_row(Table* table, const std::string& new_row);
	// serialize row to portable text-data and then save it data into destination Table
	void serialize_row(table_row* new_row, Table* table);
	// takes in serialized data(string), spits out C++ row object
	void deserialize_row(std::string serialized_row, table_row* destination);

	void print_row(table_row* row);
}
