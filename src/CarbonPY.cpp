#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "pystdlib.hpp"

std::ofstream output_cpp_file;

// Function to read the entire content of a file into a string
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

// Helper to check if a string starts with "os.system("
bool startsWithOSSystem(const std::string& input_string) {
    const std::string os_prefix = "os.system(";
    return input_string.find(os_prefix) == 0;
}

bool startsWithTime(const std::string& input_time) {
    const std::string time_prefix = "time.sleep(";
    return input_time.find(time_prefix) == 0;
}

// Function to start the compilation process (The updated logic)
void compile_python_source(const std::string& source_code) {
    std::cout << "Starting compilation of Python source code..." << std::endl;

    output_cpp_file.open("generated_output.cpp");
    if (!output_cpp_file.is_open()) { 
        std::cerr << "Error: Could not open output file for writing C++ code." << std::endl;
        return;
    }

    // Use this set to track necessary imports
    std::vector<std::string> required_headers = { "#include <iostream>", "#include <string>" };
    bool os_lib_required = false; // Flag to see if we need <cstdlib>
    bool time_lib_required = false; // Flag to see if we need <thread>, <chrono>

    output_cpp_file << "int main() {\n"; // Start a simple main function

    // Iterate line by line through the source code
    std::stringstream ss(source_code);
    std::string line;
    while (std::getline(ss, line, '\n')) {
        // Basic trim for demonstration purposes
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (line.empty() || line.rfind('#', 0) == 0) continue; // Skip empty lines/comments

        std::string cpp_line;

        if (startsWithPrint(line)) {
            // Extract content between parentheses for print
            size_t start_pos = line.find("(") + 1;
            size_t end_pos = line.rfind(")");
            if (end_pos > start_pos) {
                std::string content = line.substr(start_pos, end_pos - start_pos);
                // Use the multi-argument generator from pystdlib.hpp
                cpp_line = Generate_Cpp_Print_Code(content);
            }
        }
        else if (startsWithOSSystem(line)) {
            os_lib_required = true; // Set flag that we need cstdlib
            // Extract content between parentheses for os.system
            size_t start_pos = line.find("(") + 1;
            size_t end_pos = line.rfind(")");
            if (end_pos > start_pos) {
                std::string command_args = line.substr(start_pos, end_pos - start_pos);
                // Use the OS code generator
                // NOTE: We assume command_args is a single string literal already in Python code, e.g., "ls -l"
                cpp_line = Generate_Cpp_OS_Code(command_args);
            }
        }
        else if (startsWithTime(line)) {
            time_lib_required = true; // Set flag that we need <thread>, <chrono>
            size_t start_pos = line.find("(") + 1;
            size_t end_pos = line.rfind(")");
            if (end_pos > start_pos) {
                std::string command_args = line.substr(start_pos, end_pos - start_pos);
                // Use the OS code generator
                // NOTE: We assume command_args is a single string literal already in Python code, e.g., "ls -l"
                cpp_line = Generate_Cpp_Time_Code(command_args);
            }
        }
        if (includesint(line)) {
            // Converts "h = 5" -> "int h = 5;"
            cpp_line = Generate_Cpp_Int_Code(line);
        }

        // Write the generated line to the output file if we generated anything
        if (!cpp_line.empty()) {
            output_cpp_file << "    " << cpp_line << "\n";
        }
    }

    output_cpp_file << "    return 0;\n"; // End main function
    output_cpp_file << "}\n";
    output_cpp_file.close();

    // --- SECOND PASS TO ADD HEADERS ---
    // A robust compiler would manage headers more gracefully, 
    // but for this structure, we have to reopen and prepend the file content.
    if (os_lib_required) {
        required_headers.push_back("#include <cstdlib>");
    }
    if (time_lib_required) {
        required_headers.push_back("#include <thread>");
        required_headers.push_back("#include <chrono>");
    }

    // Read the generated content we just wrote
    std::string generated_content = read_file_contents("generated_output.cpp");
    output_cpp_file.open("generated_output.cpp", std::ios::trunc); // Reopen, wiping content

    // Write all headers first
    for (const std::string& header : required_headers) {
        output_cpp_file << header << "\n";
    }
    output_cpp_file << "\n";

    // Write the main function back in
    output_cpp_file << generated_content;
    output_cpp_file.close();

    std::cout << "Compilation complete. C++ code written to generated_output.cpp" << std::endl;
}


// The main entry point of the AOT compiler (remains unchanged)
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