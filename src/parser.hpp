#pragma once

#include <string>
#include <fstream>
#include <iostream>

class Parser
{
public:
    Parser(std::string input_file);
    void parse();

private:
    std::fstream stream;
};