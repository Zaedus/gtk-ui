#pragma once

#include "token.hpp"

#include <string>
#include <vector>

class Parser
{
private:
    std::string str;

public:
    Parser(std::string file, std::vector<std::string> libs);

    Token parse();

    /**
     * Components
     */

    Token program();
    Token numberic_literal();
};