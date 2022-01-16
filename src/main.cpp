#include "cxxopts.hpp"

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    // Define options
    cxxopts::Options options{"gtkui", "Transpiler for the Gtk UI language"};

    options.positional_help("[INPUT]");
    options.parse_positional({"input"});

    options.add_options()
        ("h,help", "Print usage")
        ("o,output", "Output file");

    // Parse options
    auto result = options.parse(argc, argv);

    // Show help dialog
    if (result.count("help") || result.arguments().size() == 0)
    {
        cout << options.help() << endl;
        exit(EXIT_SUCCESS);
    }

    
}