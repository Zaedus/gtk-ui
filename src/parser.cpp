#include "parser.hpp"
#include "common.hpp"
#include "tokenizer.hpp"

#include <fstream>
#include <fmt/format.h>

using std::string;
using std::vector;
using std::ifstream;

Parser::Parser(string file, vector<string> libs)
: tokenizer{str}
{
    ifstream ifs(file);
    if(ifs.is_open())
    {
        str = string(
            (std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>())
        );
    }
    else throw std::runtime_error{fmt::format("File '{}' not found", file)};
}

Token Parser::parse()
{
    return program();
}

Token Parser::program()
{
    return numberic_literal();
}

Token Parser::numberic_literal()
{
    return tokenizer.get_next_token();
}
