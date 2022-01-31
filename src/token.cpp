#include "token.hpp"

#include <exception>
#include <fmt/format.h>

using std::string;

Token::Token(string v)
: Token(v.c_str())
{}

Token::Token(const char *s)
{
    char *c_str = (char *)malloc(strlen(s));
    strcpy(c_str, s);
    
    value = new TokenValue(c_str);
    type = TokenType::STRING;
}

Token::Token(char *s)
{
    value = new TokenValue(s);
    type = TokenType::STRING;
}

Token::Token(bool b)
{
    value = new TokenValue(b);
    type = TokenType::BOOL;
}

Token::Token(long int n)
{
    value = new TokenValue(n);
    if (n == NULL) type = TokenType::INTERNAL_NULL;
    else type = TokenType::NUMBER;
}

Token::Token()
{
    value = new TokenValue(NULL);
    type = TokenType::INTERNAL_NULL;
}

const char * Token::type_to_string(TokenType type)
{
    return token_type_strs[type];
}
