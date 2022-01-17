#include "common.hpp"
#include "colors.hpp"

#include <iostream>
#include <fmt/format.h>

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
         << "\t" << line << endl
         << "\t" << fmt::format("{}{:>{}}", COLOR_GREEN, "^", line_char + 1) << endl;
    exit(EXIT_FAILURE);
}