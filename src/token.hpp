#pragma once

#include <string>
#include <new>

enum TokenType
{
    STRING,
    NUMBER,
    BOOL
};

typedef union token_value
{
    char *string;
    long int number;
    bool boolean;

    token_value(long int n) : number{n} {};
    token_value(bool b) : boolean{b} {};
    token_value(char *s) : string{s} {};
} TokenValue;

class Token
{
public:
    Token(std::string value);
    Token(char *value);
    Token(long int n);
    Token(bool b);

private:
    TokenType type;
    TokenValue *value;
};
