#pragma once

#include <string>
#include <string_view>
#include <sstream>
#include <iomanip>
#include <regex>

struct macro_result
{
	macro_result(std::string name, std::string file, std::string matched)
		: name(name)
		, file(file)
		, matched(matched)
	{}

	std::string name;
	std::string file;
	std::string matched;
};

using MatchVec = std::vector<macro_result>;

namespace includr
{
	const std::regex macro_pattern(R"~(INCLUDR\s*\(\s*(\w+)\s*,\s*"([\w.]+)"\s*\))~");

	MatchVec search_file(std::string content);
	std::string generate_data(const MatchVec& matches);

	inline std::string string_to_hex(std::string_view str)
	{
		std::stringstream hex_stream;

		hex_stream << "\t";
		hex_stream << std::hex << std::setfill('0') << std::setw(2);
		for (std::size_t i = 0; i < str.size(); i++)
		{
			auto ch = static_cast<unsigned char>(str[i]);
			hex_stream << "0x" << static_cast<unsigned int>(ch) << (i != str.size() - 1 ? ", " : "");

			if (i % 16 == 15 && i != str.size() - 1)
				hex_stream << "\n\t";
		}

		return hex_stream.str();
	};
}
