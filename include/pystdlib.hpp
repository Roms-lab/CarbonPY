// pystdlib.hpp
#ifndef PYSTDLIB_HPP
#define PYSTDLIB_HPP

#include <iostream>
#include <string>
#include <fstream>

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

bool includestime(const std::string& input_time) {
    const std::string time_prefix = "time.sleep(";

    if (input_time.find(time_prefix) == 0) {
        return true;
    }
    return false;
}

#endif // PYSTDLIB_HPP
