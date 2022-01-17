#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <map>

enum ParsingState {
    DEFAULT,
    DIRECTIVE,
    DEFINITION,
    ENUM
};

static const char *ParsingStateStrings[] = {
    "default",
    "directive",
    "definition",
    "enum"
};

typedef struct _parser_definition Definition;

struct _parser_definition {
    std::string name;
    std::map<std::string, std::string> props;
    std::vector<std::pair<std::string, std::string>> args;
};

class Parser
{
public:
    Parser(std::string &input_file, std::vector<std::string> &libs_path);
    void parse(std::string &root_element, std::vector<std::string> arguments);

private:
    size_t parse_between_chars(std::string &input, const char c1, const char c2, size_t position, std::string &result);
    size_t parse_string(std::string &input, size_t position, std::string &result);
    size_t parse_to_char(std::string &input, const char c, size_t position, std::string &result);
    std::string trim(const std::string &input);

    std::vector<Definition*> definitions;
    Definition *current_definition;
    std::string filename;
    std::fstream stream;
    std::vector<std::string> libs;
    ParsingState state;
};