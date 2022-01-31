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
        
        lookahead = tokenizer.get_next_token();
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
    const Token token = eat(NUMBER);
    return token;
}

Token Parser::eat(TokenType type)
{
    if (lookahead.type == type) throw std::runtime_error{fmt::format("Unexpected token: '{}', expected: '{}'", Token::type_to_string(lookahead.type), Token::type_to_string(type))};
    switch(lookahead.type)
    {
        case TokenType::INTERNAL_NULL: {
            throw std::runtime_error{fmt::format("Unexpected end of input, expected: '{}'", Token::type_to_string(type))};
            break;
        }
        case TokenType::NUMBER: {

            break;
        };
    }

}
