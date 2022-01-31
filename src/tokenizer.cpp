#include "tokenizer.hpp"

#include <iostream>

using std::string;

Tokenizer::Tokenizer(std::string &input)
: cursor{0}, input{input} 
{}

constexpr bool Tokenizer::has_more_tokens()
{
    return cursor < input.length();
}

constexpr bool Tokenizer::isEOF()
{
    return cursor == input.length();
}

Token Tokenizer::get_next_token()
{
    if (!has_more_tokens()) 
        return Token();
    
    const string segment = input.substr(cursor, string::npos);

    if (is_number(segment[0]))
    {
        string number = "";
        while (is_number(segment[cursor]))
        {
            number += segment[cursor++];
        }
        return Token{std::stol(number)};
    }
    else if (segment[0] == '"')
    {
        string str = "";
        while (segment[cursor] != '"' && !isEOF())
            str += segment[cursor++];
        return Token{str};
    }
    return Token{};
}

bool Tokenizer::is_number(char c)
{
    return c >= '0' && c <= '9';
}