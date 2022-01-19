#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <map>

enum class ParsingState {
    NONE,
    DIRECTIVE,
    DEFINITION_CONTENTS,
    DEFINITION_PROPS,
    ENUM
};

enum class ParsingSubState {
    NONE,
    PROPERTY
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
    std::map<std::string, std::pair<std::string, bool>> props;
    std::vector<std::pair<std::string, std::string>> args;
};

class Parser
{
public:
    Parser(std::string &input_file, std::vector<std::string> &libs_path);
    void parse(std::string &root_element, std::vector<std::string> arguments);

private:

    // String parsing
    size_t parse_between_chars(std::string &input, const char c1, const char c2, size_t position, std::string &result);
    size_t parse_to_char(std::string &input, const char c, size_t position, std::string &result);
    size_t parse_function_args(std::string &input, size_t position, std::vector<std::string> &result);
    std::string trim(const std::string &input);

    // Value parsing
    size_t parse_value(std::string input, std::string &result, size_t position = 0);
    size_t parse_value(std::string input, int &result, size_t position = 0);
    size_t parse_value(std::string input, bool &result, size_t position = 0);
    size_t parse_variable(std::string input, std::string &result, size_t position = 0);

    // Utils
    std::string get_state();


    std::vector<Definition*> definitions;
    Definition *current_definition;
    std::_Rb_tree_iterator<std::pair<const std::string, std::pair<std::string, bool>>> current_property;
    std::string filename;
    std::fstream stream;
    std::vector<std::string> libs;
    ParsingState state;
    ParsingSubState substate;
};
