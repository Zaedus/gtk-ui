#pragma once

#include "token.hpp"

#include <string>

class Tokenizer
{
public:
    Tokenizer(std::string &input);
    Token get_next_token();

private:
    constexpr bool has_more_tokens();
    constexpr bool isEOF();
    bool is_number(char c);

    size_t cursor;
    std::string &input;
};