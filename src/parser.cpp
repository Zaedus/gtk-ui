#include "parser.hpp"

Parser::Parser(string input_path)
: stream{input_path, ios::in}
{}