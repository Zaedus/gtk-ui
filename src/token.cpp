#include "token.hpp"

using std::string;

Token::Token(string v)
{
    value = new TokenValue(v.c_str());
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

const char * Token::type_to_string(TokenType type)
{
    return token_type_strs[type];
}
