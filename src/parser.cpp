#include "parser.hpp"

using std::cout;
using std::endl;
using std::fstream;
using std::string;
using std::vector;
using std::getline;
using std::ios;

Parser::Parser(string input_path)
: stream{input_path, ios::in}
{
    if (!stream.is_open())
        throw std::runtime_error{"File doesn't exist"};
}

void Parser::parse(string root_element, vector<string> args)
{
    string line;
    while(getline(stream, line)) {
        cout << line << endl;
    }
}