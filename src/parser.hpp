#pragma once

#include <string>
#include <fstream>
#include <iostream>

using std::string;
using std::fstream;
using std::ios;

class Parser
{
public:
    Parser(string input_file);
    void parse();

private:
    fstream stream;
};