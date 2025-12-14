#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "pystdlib.hpp"

std::ofstream output_cpp_file;

// Function to read the entire content of a file into a string (from previous steps)
std::string read_file_contents(const std::string& filepath) {
    std::ifstream file_stream(filepath);
    if (!file_stream.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << std::endl;
        return "";
    }
    std::ostringstream string_stream;
    string_stream << file_stream.rdbuf();
    file_stream.close();
    return string_stream.str();
}

// Function to start the compilation process (The code block you provided)
void compile_python_source(const std::string& source_code) {
    std::cout << "Starting compilation of Python source code..." << std::endl;

    output_cpp_file.open("generated_output.cpp");
    if (!output_cpp_file.is_open()) {
        std::cerr << "Error: Could not open output file for writing C++ code." << std::endl;
        return;
    }

    output_cpp_file << "#include <iostream>\n";
    output_cpp_file << "#include <string>\n\n";
    output_cpp_file << "int main() {\n"; // Start a simple main function

    if (startsWithPrint(source_code)) {
        size_t start_pos = source_code.find("(") + 1;
        size_t end_pos = source_code.rfind(")");

        if (start_pos != std::string::npos && end_pos != std::string::npos && end_pos > start_pos) {
            std::string content = source_code.substr(start_pos, end_pos - start_pos);
            std::string cpp_line = Generate_Cpp_Print_Code(content);
            output_cpp_file << "    " << cpp_line << "\n";
        }
    }

    output_cpp_file << "    return 0;\n"; // End main function
    output_cpp_file << "}\n";

    output_cpp_file.close();
    std::cout << "Compilation complete. C++ code written to generated_output.cpp" << std::endl;
}


// The main entry point of the AOT compiler (from previous steps)
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_python_file.py>" << std::endl;
        return 1;
    }

    std::string input_filepath = argv[1];
    std::string python_source = read_file_contents(input_filepath);

    if (python_source.empty()) {
        return 1;
    }

    compile_python_source(python_source);

    return 0;
}
