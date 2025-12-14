#include <iostream>
#include "pystdlib.hpp"

std::string Main_Start = R"(
int main() {
)";

std::string Main_End = R"(})";

void InputFile() {
	std::string File_Path;
	std::cout << "PY File Path: ";
	std::cin >> File_Path;
}

int main() {
	std::cout << Main_Start;
	std::cout << Main_End;
}