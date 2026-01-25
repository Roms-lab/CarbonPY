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

### Examples
**Relative path**
```bash
.\CarbonPy.exe script.py
```

**Absolute path**
```bash
.\CarbonPy.exe C:\Projects\Source\script.py
```

### What CarbonPy Does Internally
1. Parses the Python source file
2. Generates equivalent C++ code
3. Invokes the system compiler
4. Outputs a native executable

## 📚 Supported Libraries
- os (partial)
- time

## ⚠️ Special Requirements
To ensure CarbonPy generates valid C++:
- Do **not** rename imports
  - ✔️ `import time` → `time.sleep()`
  - ✖️ `import time as t`
  - ✖️ `from time import *`

Violating these rules will cause a compilation error.

## 📝 Changelog
### v0.0.1 — Initial Release
- Added support for string literal output via `print("Hello World")`
- Implemented basic CLI for invoking CarbonPy

### v0.0.2
- Added support for `os.system()`

### v0.0.3
- Added support for `time.sleep()`
- Fixed issue where quotes were removed inside `os.system()` calls

### v0.0.4
- Added integer variable conversion: `Var1 = 5` → `int Var1 = 5;`
