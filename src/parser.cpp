#include "parser.hpp"
#include "colors.hpp"

#include <fmt/format.h>

using std::cout;
using std::endl;
using std::fstream;
using std::string;
using std::vector;
using std::getline;
using std::ios;

namespace fs = std::filesystem;

Parser::Parser(string input_path, vector<string> libs_path)
: stream{input_path, ios::in},
  state{ParsingState::DEFAULT}
{
    if (!stream.is_open())
        throw std::runtime_error{"File doesn't exist"};
    
    for (string &path : libs_path)
    {
        if (fs::is_directory(path)) libs.push_back(path);
    }
}

void Parser::parse(string root_element, vector<string> args)
{
    string line;
    while(getline(stream, line)) {
        if (state == ParsingState::DIRECTIVE) state = ParsingState::DEFAULT;

        for (size_t i = 0; i < line.length(); ++i) {
            switch (line[i])
            {
                case '\t':
                case ' ':
                    continue;
                case '#':
                    if (state != ParsingState::DEFAULT) fail(fmt::format("Attempted to parse directive when parsing {}", ParsingStateStrings[state]));
                    ++i;
                    state = ParsingState::DIRECTIVE;
                    
                    string substr = line.substr(i, line.find(' ', i) - i);
                    if (substr == "include")
                    {
                        i += 8;

                        string name;
                        i += parse_string(line, i, name);
                    }
                    continue;
            }
            cout << line[i];
        }
        cout << endl;
    }
}

size_t Parser::parse_string(std::string input, size_t position, std::string &result)
{
    size_t start_pos = input.find('"', position) + 1;
    size_t end_pos = input.find('"', start_pos);
    result = input.substr(start_pos, end_pos - start_pos);

    return end_pos - start_pos + 1;
}

void Parser::fail(string reason)
{
    cout << COLOR_ERROR << "parsing error: " << COLOR_RESET << reason << endl;
    exit(EXIT_FAILURE);
}