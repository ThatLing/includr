
#include <cstdio>
#include <string>

#include "fs.h"
#include "includr.h"


int main(int argc, const char** argv)
{
	printf("[includr] Starting (%s)\n", __DATE__);

	// Parse command line
	// TODO: Add support for folder/multiple files
#ifndef DEBUG
	if (argc < 2)
	{
		printf("[includr] No input file provided\n");
		printf("usage: includr.exe <file>\n");
		return 0;
	}

	fs::path file(argv[1]);
#else
	fs::path file("test.txt");
#endif

	// Check file
	if (!fs::exists(file))
	{
		printf("[includr] Could not find input file '%s'\n", file.u8string().c_str());
		return 0;
	}

	// Read file
	std::string content = fs::read_file(file);
	if (content.size() == 0)
	{
		printf("[includr] Failed to read input file '%s'\n", file.u8string().c_str());
		return 0;
	}

	// Do magic
	auto matches = includr::search_file(content);
	auto file_content = includr::generate_data(matches);

	printf("[includr] Done, writing to '%s'\n", "includr_data.cpp");

	fs::write_file("includr_data.cpp", file_content);

	return 1;
}
