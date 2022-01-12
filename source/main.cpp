
#include <cstdio>
#include <string>

#include "fs.h"
#include "includr.h"


int main(int argc, const char** argv)
{
	// Parse command line
	// TODO: Add support for folder/multiple files
#ifndef DEBUG
	if (argc < 2)
	{
		printf("No input file provided");
		return 0;
	}

	fs::path file(argv[1]);
#else
	fs::path file("test.txt");
#endif

	if (!fs::exists(file))
	{
		printf("Could not find input file '%s'", file.u8string().c_str());
		return 0;
	}

	std::string content = fs::read_file(file);
	if (content.size() == 0)
	{
		printf("Failed to read input file '%s'", file.u8string().c_str());
		return 0;
	}

	auto matches = includr::search_file(content);
	auto file_content = includr::generate_data(matches);

	fs::write_file("data.c", file_content);

	return 1;
}
