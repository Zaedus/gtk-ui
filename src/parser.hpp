#pragma once

#include <string>
#include <vector>

class Parser
{
public:
    Parser(std::string file, std::vector<std::string> libs);

    void parse();
};