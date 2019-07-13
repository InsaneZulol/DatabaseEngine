#pragma once
#include <string>
#include <variant>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace table
{
	inline struct table_row
	{
		int id;
		std::string name;
		std::string email;
	} row; // row is a global variable in table namespace.
}

// We need to tell fusion about our employee struct
// to make it a first-class fusion citizen. This has to
// be in global scope.
BOOST_FUSION_ADAPT_STRUCT(
	table::table_row,
	(int, id)
	(std::string, name)
	(std::string, email)
)

namespace parser
{
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	//  
	// Our table_row parser grammar
	// possible better design for later:
	// https://stackoverflow.com/questions/42811884/boostspirit-struggle-with-parsing-a-string
	//
	template <typename Iterator>
	struct insert_grammar : qi::grammar<Iterator, table::table_row(), ascii::space_type>
	{
		insert_grammar() : insert_grammar::base_type(start_)
		{
			using qi::int_;
			using qi::lit;
			using qi::lexeme;
			using ascii::char_;
			using ascii::space;

			name_ %= lexeme[+(char_ - space)];
			email_ %= lexeme[+ascii::alnum
				>> *(qi::char_(".") >> +ascii::alnum)
				>> qi::char_("@")
				>> +ascii::alnum
				>> +(qi::char_(".") >> +ascii::alnum)];

			start_ %=
				lit("insert")
				>> int_
				>> name_
				>> email_;
			//// uncomment in case of issues with parsing
			// BOOST_SPIRIT_DEBUG_NODES((start)(name)(email))
		}

	private:
		qi::rule<Iterator, std::string(), ascii::space_type> name_;
		qi::rule<Iterator, std::string(), ascii::space_type> email_;
		qi::rule<Iterator, table::table_row(), ascii::space_type> start_;
	};
}