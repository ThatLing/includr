#pragma once

#include <string>
#include <string_view>
#include <sstream>
#include <iomanip>
#include <regex>
#include <map>
#include <cstdint>
#include <vector>

#include "fastlz.h"

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
	std::uint8_t xor_key = 0;
	bool compress = false;
};

using Matches = std::map<std::string, macro_result>;
using ByteArray = std::vector<std::uint8_t>;

namespace includr
{
	const std::regex macro_pattern(R"~(INCLUDR\s*\(\s*(\w+)\s*,\s*"([\w.]+)"\s*\))~");
	const std::regex xor_macro_pattern(R"~(INCLUDR_XOR\s*\(\s*(\w+)\s*,\s*0x([\da-fA-F]+)\s*\))~");
	const std::regex compress_macro_pattern(R"~(INCLUDR_COMPRESS\s*\(\s*(\w+)\s*\))~");

	Matches search_file(std::string content);
	std::string generate_data(const Matches& matches);

	inline std::string string_to_hex(ByteArray& bytes)
	{
		std::stringstream hex_stream;

		hex_stream << "\t";
		hex_stream << std::hex << std::setfill('0') << std::uppercase;
		for (std::size_t i = 0; i < bytes.size(); i++)
		{
			auto ch = static_cast<unsigned char>(bytes[i]);
			hex_stream << "0x" << std::setw(2) << static_cast<unsigned int>(ch) << (i != bytes.size() - 1 ? ", " : "");

			if (i % 16 == 15 && i != bytes.size() - 1)
				hex_stream << "\n\t";
		}

		return hex_stream.str();
	}

	inline void compress(ByteArray& bytes)
	{
		std::uint32_t max_size = bytes.size() * 1.05;
		if (max_size < 66)
			max_size = 66;

		while (bytes.size() < 16)
			bytes.push_back(0);

		char* compressed = (char*)malloc(max_size);
		int len = fastlz_compress_level(2, bytes.data(), bytes.size(), compressed);

		bytes = ByteArray(compressed, compressed + len);
	}

	inline void xor_string(ByteArray& bytes, std::uint8_t key)
	{
		for (std::size_t i = 0; i < bytes.size(); i++)
		{
			bytes[i] = bytes[i] ^ key;
		}
	}
}
