#pragma once

#include <string>
#include <fstream>
#include <iostream>

class Parser
{
public:
    Parser(string input_file);
    void parse();

private:
    std::fstream stream;
};