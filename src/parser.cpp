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
    return literal();
}

Token Parser::literal()
{
    switch (lookahead.type)
    {
        case TokenType::NUMBER: 
            return numeric_literal();
        case TokenType::STRING: 
            return string_literal();
        case TokenType::BOOL:
            // return bool_literal();
            break;
        case TokenType::INTERNAL_NULL:
            throw std::runtime_error{"Invalid token found"};
            break;
    }
    throw std::runtime_error{fmt::format("Expected literal, literal not found")};
}

Token Parser::numeric_literal()
{
    const Token token = eat(TokenType::NUMBER);
    return token;
}

Token Parser::string_literal()
{
    const Token token = eat(TokenType::STRING);
    return token;
}

Token Parser::eat(TokenType type)
{
    Token token = lookahead;
    if (token.type != type) throw std::runtime_error{fmt::format("Unexpected token: '{}', expected: '{}'", Token::type_to_string(token.type), Token::type_to_string(type))};
    else if (token.type == TokenType::INTERNAL_NULL) throw std::runtime_error{fmt::format("Unexpected end of input, expected: '{}'", Token::type_to_string(type))};
    
    lookahead = tokenizer.get_next_token();

    return token;
}
