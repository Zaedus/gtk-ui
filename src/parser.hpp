#pragma once

#include "token.hpp"
#include "tokenizer.hpp"

#include <string>
#include <vector>

class Parser
{
private:
    // Util Functions
    Token eat(TokenType type);

    /**
     * Components
     */
    Token program();
    Token literal();
    Token numeric_literal();
    Token string_literal();

    std::string str;
    Token lookahead;
    Tokenizer tokenizer;

public:
    Parser(std::string file, std::vector<std::string> libs);

    Token parse();
};
