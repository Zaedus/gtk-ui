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

static const char * ParsingStateStrings[] = {
    "default",
    "directive",
    "definition",
    "enum"
};

class Parser
{
public:
    Parser(std::string input_file, std::vector<std::string> libs_path);
    void parse(std::string root_element, std::vector<std::string> arguments);

private:

    size_t parse_between_chars(std::string &input, const char c1, const char c2, size_t position, std::string &result);
    size_t parse_string(std::string &input, size_t position, std::string &result);
    size_t parse_to_char(std::string &input, const char c, size_t position, std::string &result);

    std::string filename;
    std::fstream stream;
    std::vector<std::string> libs;
    ParsingState state;
};