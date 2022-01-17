#pragma once

#include <string>

void fail(std::string reason);
void fail_line(std::string reason, std::string &line, std::string &filename, size_t &line_number, size_t &line_char);