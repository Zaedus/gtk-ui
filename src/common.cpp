#include "common.hpp"
#include "colors.hpp"

#include <iostream>

using std::string;
using std::cout;
using std::endl;

void fail(string reason)
{
    cout << COLOR_ERROR << "error: " << COLOR_RESET << reason << endl;
    exit(EXIT_FAILURE);
}

void fail_line(string reason, string &line, string &filename, size_t &line_number, size_t &line_char)
{
    cout << COLOR_BOLD << filename << ":" << line_number << ":" << line_char << ": " << COLOR_ERROR << "error: " << COLOR_BOLD << reason << COLOR_RESET << endl
         << line << endl;
}