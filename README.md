# CarbonPy
A High-Performance Python-to-C++ Compiler
## Project Overview
CarbonPy is an innovative compilation system designed to bridge the gap between the expressive power of the Python programming language and the computational efficiency of native C++.
This project functions as a dynamic Ahead-Of-Time (AOT) compiler that translates a robust subset of Python source code into optimized C++ intermediate representations. It then leverages established system compilers, such as the Microsoft Visual C++ (MSVC) toolchain, to generate highly efficient machine code binaries.
The objective of CarbonPy is to enable Python developers to achieve near-native performance for CPU-intensive algorithms and streamline application deployment without the overhead of a traditional interpreter runtime.
### Compiling and Usage
The CarbonPy compiler is invoked via a command-line interface (CLI) to process Python source files and generate native executables.
CLI Syntax
Navigate to the directory containing the CarbonPy.exe executable and provide the path to your Python source file as an argument.
bash
```
.\CarbonPy.exe <file_path>.py
```

Relative Paths: If the Python file is located in the same directory as the executable, you may provide just the filename (e.g., ```.\CarbonPy.exe script.py).```
Absolute Paths: If the file is in a different location, provide the full absolute path to the file (e.g., ```.\CarbonPy.exe C:\Projects\Source\script.py).```
Compilation Process (Behind the Scenes)
The CLI tool parses the specified Python file.
It dynamically generates corresponding C++ source code.
The resulting executable is placed in the output directory.
### Changelog
- ***Version 0.0.1 (Initial Release)***
- **Added: Initial support for simple string literal conversion using the print() statement syntax (e.g., print("Hello World")).**
- **Added: Basic command-line interface for invoking the compiler executable (CarbonPy.exe).**
  
- ***Version 0.0.2***
- **Added os.system() Support**

- ***Version 0.0.3***
- **Added time.sleep() Support**
- **Fixed Forced Removal of quotes in os.system()**

### Supported Libraries
- OS

### Special Edits
***For CarbonPY to work you must change some things, so here is a list on how to make CarbonPY generate correct code.***
- ***```All imports must NOT be renamed, or used as a wildcard```***
- ***```For Example. Time Lib MUST be time.sleep() or the compiler will throw an error.```***
