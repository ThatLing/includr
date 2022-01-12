#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <sstream>

namespace includr
{
	using ByteArray = const std::vector<std::uint8_t>;

	class IncludrFile
	{
	public:
		IncludrFile(ByteArray bytes)
			: bytes(bytes)
		{}

		std::string ToString()
		{
			std::string out;
			out.reserve(bytes.size());
			
			for (std::uint8_t byte : bytes)
			{
				out.push_back(byte);
			}

			return out;
		}

	private:
		ByteArray bytes;
	};
}

