#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>

enum ParsingState {
    DEFAULT,
    DIRECTIVE,
    DEFINITION,
    ENUM
};

class Parser
{
public:
    Parser(std::string input_file, std::vector<std::string> libs_path);
    void parse(std::string root_element, std::vector<std::string> arguments);

private:
    size_t parse_string(std::string input, size_t position, std::string &result);

    std::fstream stream;
    std::vector<std::string> libs;
    ParsingState state;
};