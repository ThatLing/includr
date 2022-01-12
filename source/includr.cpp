
#include "includr.h"

#include <iterator>

#include "fs.h"

MatchVec includr::search_file(std::string content)
{
	MatchVec results;

	std::smatch sm;
	while (std::regex_search(content, sm, includr::macro_pattern))
	{
		results.emplace_back(sm[1], sm[2], sm[0]);
		content = sm.suffix();
	}

	return results;
}

std::string includr::generate_data(const MatchVec& matches)
{
	std::stringstream ss;

	// Generate boilerplate
	ss << "#include \"includr.h\"\n\n";
	ss << "#ifdef __cplusplus\n";
	ss << "#extern \"C\" {\n";
	ss << "#endif\n\n";


	// Generate files
	for (macro_result match : matches)
	{
		ss << "// " << match.matched << "\n";
		
		if (!fs::exists(match.file))
		{
			ss << "#error Could not find file '" << match.file << "'\n\n";
			printf("; Could not find file '%s', skipping!\n", match.file.c_str());
			continue;
		}

		std::string file_content = fs::read_file(match.file);
		if (file_content.size() == 0)
		{
			ss << "#error Failed to read file '" << match.file << "'\n\n";
			printf("; Failed to read file '%s', skipping!\n", match.file.c_str());
			continue;
		}

		ss << "includr::IncludrFile " << match.name << "({\n";
		ss << includr::string_to_hex(file_content) << "\n});\n\n";
	}


	// More boilerplate
	ss << "#ifdef __cplusplus\n";
	ss << "}\n";
	ss << "#endif\n\n";

	return ss.str();
}
