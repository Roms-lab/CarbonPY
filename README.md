# CarbonPy
### A High-Performance Python-to-C++ Compiler

CarbonPy is a lightweight Ahead-Of-Time (AOT) compiler that translates a supported subset of Python into optimized C++ code, then uses system compilers (MSVC, GCC, Clang) to produce fast, native executables. It is designed for developers who want Python-like syntax with near-C++ performance and no interpreter overhead.

## 🚀 Features
- Translates Python code into C++ intermediate output
- Compiles to native machine code using your system toolchain
- Cross-platform builds (Windows, Linux, macOS)
- Simple CLI interface
- Early support for core Python features and standard library functions

## 📦 Usage
From the directory containing the CarbonPy executable:
```bash
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
- OS ***(Partial Support)***
- Time

### Special Edits
***For CarbonPY to work you must change some things, so here is a list on how to make CarbonPY generate correct code.***
- ***```All imports must NOT be renamed, or used as a wildcard```***
- ***```For Example. Time Lib MUST be time.sleep() or the compiler will throw an error.```***
