#include "cxxopts.hpp"
#include "colors.hpp"
#include "parser.hpp"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv)
{
    // Define option vars
    string input_file;
    string output_file;

    // Define options
    cxxopts::Options options{"gtkui", "Transpiler for the Gtk UI language"};

    options.positional_help("[INPUT]");
    options.parse_positional({"input"});

    options.add_options()
        ("h,help", "Print usage")
        ("i,input", "Input file", cxxopts::value<string>(input_file))
        ("o,output", "Output file", cxxopts::value<string>(output_file));

    try {
        // Parse options
        auto result = options.parse(argc, argv);

        // Show help dialog
        if (result.count("help") || result.arguments().size() == 0)
        {
            cout << options.help() << endl;
            exit(EXIT_SUCCESS);
        }

        // Parse
        Parser parser{input_file};
        parser.parse();
    } catch (const cxxopts::OptionException& e) {
        cout << COLOR_ERROR << "error: " << COLOR_RESET << e.what() << endl;
        exit(EXIT_FAILURE);
    } catch (const std::runtime_error& e) {
        cout << COLOR_ERROR << "error: " << COLOR_RESET << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}