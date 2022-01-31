#include "tokenizer.hpp"

using std::string;

Tokenizer::Tokenizer(std::string &input)
: input{input}, cursor{0}
{}

constexpr bool Tokenizer::has_more_tokens()
{
    return cursor < input.length();
}

Token Tokenizer::get_next_token()
{
    if (!has_more_tokens()) 
        return NULL;
    
    const string segment = input.substr(cursor, string::npos);

    if (is_number(segment[0]))
    {
        string number = "";
        while (is_number(segment[cursor]))
        {
            number += segment[cursor];
        }
        return Token(std::stol(number));
    }
    return NULL;
}

bool Tokenizer::is_number(char c)
{
    return c >= '0' && c <= '9';
}