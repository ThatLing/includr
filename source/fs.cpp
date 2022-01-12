
#include "fs.h"

std::string std::filesystem::read_file(fs::path path)
{
    std::ifstream file_stream(path, ios::in | ios::binary);

    std::ostringstream out_stream;
    out_stream << file_stream.rdbuf();
    return out_stream.str();
}

void std::filesystem::write_file(fs::path path, std::string content)
{
    std::ofstream file_stream(path);
    file_stream << content;
}
