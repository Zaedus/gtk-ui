#include "parser.hpp"
#include "common.hpp"

#include <fmt/format.h>
#include <sstream>

using std::cout;
using std::endl;
using std::fstream;
using std::string;
using std::vector;
using std::getline;
using std::ios;
using std::stringstream;
using std::pair;
using std::make_pair;

namespace fs = std::filesystem;

Parser::Parser(string &input_path, vector<string> &libs_path)
: filename{input_path},
  stream{input_path, ios::in},
  state{ParsingState::NONE},
  substate{ParsingSubState::NONE}
{
    if (!stream.is_open())
        throw std::runtime_error{"File doesn't exist"};
    
    for (string &path : libs_path)
    {
        if (fs::is_directory(path)) libs.push_back(path);
    }
}

void Parser::parse(string &root_element, vector<string> args)
{
    string line;
    size_t line_number = 0;
    while(getline(stream, line)) {
        line_number++;
        if (state == ParsingState::DIRECTIVE) state = ParsingState::NONE;

        for (size_t i = 0; i < line.length(); ++i) {
            switch (line[i])
            {
                case '\t':
                case ' ':
                    continue;
                case '#': {
                    if (state != ParsingState::NONE)
                        fail_line(fmt::format("Attempted to parse directive when parsing {}", get_state()), line, filename, line_number, i);
                    state = ParsingState::DIRECTIVE;
                    ++i;
                    
                    string substr;
                    i += parse_to_char(line, ' ', i, substr);

                    if (substr == "include")
                    {
                        string name;
                        i += parse_string(line, i, name);

                        bool found_lib = false;
                        
                        for (string& path : libs)
                        {
                            string file_path = fmt::format("{}/{}.gui", path, name);
                            if (fs::exists(file_path))
                            {
                                Parser file_parser{file_path, libs};
                                file_parser.parse(root_element, args);
                                found_lib = true;
                                break;
                            }
                        }

                        if (!found_lib) fail_line(fmt::format("Library '{}' not found", substr), line, filename, line_number, i);
                    } 
                    else fail_line(fmt::format("Unknown directive '{}'", substr), line, filename, line_number, i);
                    continue;
                }
                case '@': {
                    ++i;

                    // Leave definition state
                    if (state == ParsingState::DEFINITION_PROPS)
                    {
                        state = ParsingState::NONE;
                    }

                    // Enables only special definitions like Prop
                    if (state == ParsingState::DEFINITION_CONTENTS)
                    {
                        string modifier_name;
                        i += parse_to_char(line, '(', i, modifier_name);
                        
                        // Prop(property_name, property_variable)
                        if (modifier_name == "Prop")
                        {
                            substate = ParsingSubState::NONE;

                            vector<string> args;
                            i += parse_function_args(line, i, args);

                            // Verify argument integrity
                            if (args.size() != 2) 
                                fail_line("Incorrect number of arguments in property definition", line, filename, line_number, i);

                            current_property = current_definition->props.insert({args[0], {args[1], false}}).first;
                            substate = ParsingSubState::PROPERTY;
                        }
                    }
                    // Only when defining a new object
                    else if (state == ParsingState::NONE)
                    {
                        state = ParsingState::DEFINITION_CONTENTS;

                        string definition_name;
                        i += parse_to_char(line, '{', i, definition_name);

                        Definition* def = new Definition({
                            definition_name,    // Name
                            {},                 // Props
                            {}                  // Args
                        });

                        current_definition = def;
                        definitions.push_back(def);
                    }
                    else fail_line(fmt::format("Attempted to parse definition when parsing {}", get_state()), line, filename, line_number, i);
                    
                    continue;
                }
                case '}': {
                    if (state == ParsingState::DEFINITION_CONTENTS)
                    {
                        state = ParsingState::DEFINITION_PROPS;
                        substate = ParsingSubState::NONE;
                        current_definition = NULL;
                        continue;
                    }
                }
                // Comments
                case '/': {
                    if (line[i+1] == '/') i = line.length();
                    continue;
                }
                case '.': {
                    ++i;

                    if (substate == ParsingSubState::PROPERTY)
                    {
                        string function_name;
                        i += parse_to_char(line, '(', i, function_name);

                        if (function_name == "translatable")
                        {
                            vector<string> args;
                            i += parse_function_args(line, i, args);

                            if (args.size() != 1)
                                fail_line("Incorrect number of arguments", line, filename, line_number, i);
                            
                            current_property->second.second = true;

                            continue;
                        }
                        else fail_line(fmt::format("Unknown function '{}'", function_name), line, filename, line_number, i);
                    }
                    else if (state == ParsingState::DEFINITION_PROPS)
                    {

                    }
                }
            }
            cout << line[i];
        }
        cout << endl;
    }

    cout << "---------------------------------------------------" << endl;
    for (auto &def : definitions)
    {
        cout << "Title: " << def->name << endl;
        cout << "Properties: " << endl;
        for (auto &prop : def->props)
        {
            cout << prop.first << ": " << prop.second.first << " (Translatable: " << prop.second.second << ")" << endl;
        }

        cout << endl;
    }

    cout << "---------------------------------------------------" << endl;
}

string Parser::trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

size_t Parser::parse_between_chars(std::string &input, const char c1, const char c2, size_t position, std::string &result)
{
    size_t start_pos = input.find(c1, position) + 1;
    size_t end_pos = input.find(c2, start_pos);
    result = trim(input.substr(start_pos, end_pos - start_pos));

    return end_pos - start_pos + 2;
}

size_t Parser::parse_string(std::string &input, size_t position, std::string &result)
{
    return parse_between_chars(input, '"', '"', position, result);
}

size_t Parser::parse_to_char(string &input, const char c, size_t start_pos, std::string &result)
{
    size_t end_pos = input.find(c, start_pos);
    result = trim(input.substr(start_pos, end_pos - start_pos));

    return end_pos - start_pos;
}

size_t Parser::parse_function_args(std::string &input, size_t position, std::vector<string> &result)
{
    size_t length = input.find(')', position) - position;
    stringstream ss{input.substr(position + 1, length - 1)};
    string arg;

    while (getline(ss, arg, ','))
    {
        result.push_back(trim(arg));
    }
    return length;
}

string Parser::get_state()
{
    switch (state)
    {
        case ParsingState::NONE:
            return "none";
        case ParsingState::DEFINITION_CONTENTS:
            return "definition contents";
        case ParsingState::DEFINITION_PROPS:
            return "definition properties";
        case ParsingState::DIRECTIVE:
            return "directive";
        case ParsingState::ENUM:
            return "enum";
    };
}