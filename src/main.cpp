#include "cxxopts.hpp"
#include "colors.hpp"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv)
{
    // Define options
    cxxopts::Options options{"gtkui", "Transpiler for the Gtk UI language"};

    options.positional_help("[INPUT]");
    options.parse_positional({"input"});

    options.add_options()
        ("h,help", "Print usage")
        ("i,input", "Input file", cxxopts::value<string>())
        ("o,output", "Output file", cxxopts::value<string>());

    try {
        // Parse options
        auto result = options.parse(argc, argv);

        // Show help dialog
        if (result.count("help") || result.arguments().size() == 0)
        {
            cout << options.help() << endl;
            exit(EXIT_SUCCESS);
        }
    } catch (const cxxopts::OptionException& e) {
        cout << COLOR_ERROR << "error: " << COLOR_RESET << e.what() << endl;
    }
}