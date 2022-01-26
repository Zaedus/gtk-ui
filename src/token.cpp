#include "token.hpp"

Token::Token(std::string v)
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
    type = TokenType::NUMBER;
}