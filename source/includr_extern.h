#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <sstream>

#include "fastlz.h"

#define INCLUDR(name, file) extern includr::IncludrFile name;
#define INCLUDR_XOR(name, key)
#define INCLUDR_COMPRESS(name)

namespace includr
{
	using ByteArray = std::vector<std::uint8_t>;

	class IncludrFile
	{
	public:
		IncludrFile(ByteArray bytes, bool compressed, std::uint32_t length)
			: IncludrFile(bytes, 0, compressed, length)
		{}

		IncludrFile(ByteArray _bytes, std::uint8_t key = 0, bool compressed = false, std::uint32_t length = 0)
		{
			if (key != 0)
			{
				for (std::size_t i = 0; i < _bytes.size(); i++)
				{
					_bytes[i] = _bytes[i] ^ key;
				}
			}

			if (compressed)
			{
				char* out = (char*)malloc(length);

				int len = fastlz_decompress(_bytes.data(), _bytes.size(), out, length);
				_bytes = ByteArray(out, out + len);
			}

			bytes = _bytes;
		}

		std::string to_string()
		{
			std::string out;
			out.reserve(bytes.size());

			for (std::uint8_t byte : bytes)
			{
				out.push_back(byte);
			}

			return out;
		}

		const uint8_t* to_array()
		{
			return bytes.data();
		}

		std::size_t size()
		{
			return bytes.size();
		}

	private:
		ByteArray bytes;
	};
}

