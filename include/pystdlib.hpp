// pystdlib.hpp
#ifndef PYSTDLIB_HPP
#define PYSTDLIB_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>

// Function to generate the C++ equivalent string for a 'print()' call
std::string Generate_Cpp_Print_Code(const std::string& content_to_print) {
    // This is the core conversion logic
    std::string cpp_code = "std::cout << " + content_to_print + " << std::endl;";
    return cpp_code;
}

std::string Generate_Cpp_OS_Code(const std::string& command_to_execute) {
    std::string cpp_code = "system(" + command_to_execute + ");";
    return cpp_code;
}

std::string Generate_Cpp_Time_Code(const std::string& time_to_wait) {
    std::string cpp_code = "std::this_thread::sleep_for(std::chrono::seconds(" + time_to_wait + "));";
    return cpp_code;
}

std::string Generate_Cpp_Int_Code(const std::string& line) {
    size_t eq_pos = line.find('=');
    
    // Extract variable name and value
    std::string var_name = line.substr(0, eq_pos);
    std::string value = line.substr(eq_pos + 1);

    // Clean up whitespace for valid C++ syntax
    var_name.erase(var_name.find_last_not_of(" \t") + 1);
    var_name.erase(0, var_name.find_first_not_of(" \t"));
    
    // Remove the Python trailing colon if it exists
    size_t colon_pos = value.find(':');
    if (colon_pos != std::string::npos) value = value.substr(0, colon_pos);

    return "int " + var_name + " =" + value + ";";
}

// Function to check if a string starts with "print("
bool startsWithPrint(const std::string& input_string) {
    const std::string print_prefix = "print(";

    // Check if the prefix is found exactly at the beginning (index 0)
    if (input_string.find(print_prefix) == 0) {
        return true;
    }
    return false;
}

bool includesos(const std::string& input_string) {
    const std::string os_prefix = "os.system(";

    if (input_string.find(os_prefix) == 0) {
        return true;
    }
    return false;
}

bool includesint(const std::string& line) {
    size_t eq_pos = line.find('=');
    if (eq_pos == std::string::npos) return false;

    // Look for the first digit after the '='
    size_t first_digit = line.find_first_of("0123456789", eq_pos);
    
    // Return true if a digit exists after the equals sign
    return (first_digit != std::string::npos);
}

bool includestime(const std::string& input_time) {
    const std::string time_prefix = "time.sleep(";

    if (input_time.find(time_prefix) == 0) {
        return true;
    }
    return false;
}

#endif // PYSTDLIB_HPP
