#pragma once

#include "token.hpp"
#include "tokenizer.hpp"

#include <string>
#include <vector>

class Parser
{
private:
    std::string str;
    Tokenizer tokenizer;

public:
    Parser(std::string file, std::vector<std::string> libs);

    Token parse();

    /**
     * Components
     */

    Token program();
    Token numberic_literal();
};