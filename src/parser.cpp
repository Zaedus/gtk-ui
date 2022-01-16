#include "parser.hpp"

using std::cout;
using std::fstream;
using std::string;
using std::getline;
using std::ios;

Parser::Parser(string input_path)
: stream{input_path, ios::in}
{
    if (!stream.is_open())
        throw std::runtime_error{"File doesn't exist"};
}

void Parser::parse()
{
    string line;
    while(getline(stream, line)) {
        
    }
}