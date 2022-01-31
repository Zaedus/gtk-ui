#pragma once

#include <string>
#include <new>

enum TokenType
{
    STRING,
    NUMBER,
    BOOL,
    INTERNAL_NULL
};

static const char *token_type_strs[] =
{
    "STRING",
    "NUMBER",
    "BOOLEAN",
    "INTERNAL_NULL"
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
    Token(const char *value);
    Token(char *value);
    Token(long int n);
    Token(bool b);
    Token();

    static const char * type_to_string(TokenType type);

    TokenType type;
    TokenValue *value;
};
