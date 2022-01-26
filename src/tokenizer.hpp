#pragma once

#include "token.hpp"

#include <string>

class Tokenizer
{
public:
    Tokenizer(std::string &input);

private:
    long int cursor;
    std::string &input;
};