#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;

namespace std::filesystem
{
	std::string read_file(fs::path path);
	void write_file(fs::path path, std::string content);
}
