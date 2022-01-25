#pragma once

#include <any>

enum TokenType
{
    STRING,
    NUMBER
};

class Token
{
public:
    

private:
    TokenType type;
    std::any value;
};

class Tokenizer
{
    
};