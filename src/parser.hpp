#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class Parser
{
public:
    Parser(std::string input_file);
    void parse(std::string root_element, std::vector<std::string> arguments);

private:
    std::fstream stream;
};