#include <fstream>
#include <iostream>
#include <filesystem>

#include "FileList/FileList.h"
namespace fs = std::filesystem;

int main (int argc, char* argv[]) {
    PufferMake::FileList source_files;
    source_files.AddFilterExtension(L"c");
    source_files.AddFilterExtension(L"cc");
    source_files.AddFilterExtension(L"cpp");
    source_files.AddFilterExtension(L"CPP");
    source_files.AddFilterExtension(L"c++");
    source_files.AddFilterExtension(L"cp");
    source_files.AddFilterExtension(L"cxx");

    PufferMake::FileList header_files;
    header_files.AddFilterExtension(L"h");
    header_files.AddFilterExtension(L"hh");
    header_files.AddFilterExtension(L"hpp");
    header_files.AddFilterExtension(L"H");

    PufferMake::FileList object_files;
    object_files.AddFilterExtension(L"o");

    PufferMake::FileList preprocessed_files;
    preprocessed_files.AddFilterExtension(L"i");
    preprocessed_files.AddFilterExtension(L"ii");
    
    fs::path cwd = "./";
    fs::current_path(cwd);
 
    for (auto const& dir_entry : fs::recursive_directory_iterator(cwd)) {
        if (dir_entry.is_directory()) {
            continue;
        }
        auto current_path = dir_entry.path().wstring();
        auto path_without_cwd = current_path.substr(2);
        if (path_without_cwd.at(0) == '.') {
            continue;
        }

        source_files.TryAddFile(current_path);
        header_files.TryAddFile(current_path);
        object_files.TryAddFile(current_path);
        preprocessed_files.TryAddFile(current_path);
        
    }

    std::wcout << "\nSource files:" << '\n';
    source_files.PrintFiles();

    std::wcout << "\nHeader files:" << '\n';
    header_files.PrintFiles();

    std::wcout << "\nObject files:" << '\n';
    object_files.PrintFiles();

    std::wcout << "\nPreprocessed files:" << '\n';
    preprocessed_files.PrintFiles();

    return 0;
}

/* 
run commands:

g++ -c src/main.cpp src/FileList/FileList.cpp src/nlohmann/json.hpp src/Configuration/Configuration.cpp -std=c++20 -Os
g++ main.o FileList.o json.o Configuration.o -o ./target/app
./target/app

*/

// C++ source files: .c .cc .cpp .CPP .c++ .cp .cxx
// C++ header files: .h .hh .hpp .H
// C++ preprocessed files: .ii .i


// dosyayı compile etmek için:
// g++ -c main.cpp -std=c++20 -Os

// -D macroname     : defines the specified macro for compilation.
// -U macroname     : undefines it.

// to see preprocessed file
// g++ -E main.cpp
// specifying -nostdinc bypasses standard include files.

// -fpic (or -fPIC) : position independent code for shared libraries.
// -I"dir"          : include directory


// link etmek için:
// g++ main.o -o ./target/app

// -g0     : no debug info
// -g1     : minimal debug info
// -g      : default debug info
// -g3     : maximal debug info
// -ggdb   : use most expressive format for gdb use.
// -gdwarf : produce debug info in DWARF format.

// --------------------------------------------------------------------------- |
// optimizations | execution time | code size | memory usage | compile time    |
// --------------|----------------|-----------|--------------|---------------  |
// -O0 :         | increases      | increases | reduces      | reduces         | for compilation time
// -O1 or -O :   | reduces        | reduces   | increases    | increases       | for code size and execution time
// -O2 :         | reduces+       |           | increases    | increases+      | for code size and execution time ++
// -O3 :         | reduces++      |           | increases    | increases+++    | for code size and execution time ++ ++
// -Os :         |                | reduces+  |              | increases+      | for code size
// -Ofast :      | reduces++      |           | increases    | increases+++    | same as -O3 with fast non-accurate math
// --------------------------------------------------------------------------- |
// -Og : optimize for debugging experience
// -Oz : aggressive optimization for size rather than speed.

// aşağıdaki komut statik olarak math kütüphanesini linkler
// g++ -static myfile.o -lmath -o myfile

// aşağıdaki komut dinamik olarak math kütüphanesini linkler
// g++ myfile.o -lmath -o myfile

// -L"dir" : library directory

// -o outputfile : outputs to outputfile



/*
option descriptions
-ansi         : -std=c90 for C, -std=c++98 for C++
-w            : disable all warning messages
-fsyntax-only : check only for syntax errors
-Werror       : make all warnings into errors.
-Wall         : enables all the warnings regarding constructions.
-Wextra       : all flags that -Wall did not enable.
-Wabi         : probable abi warnings.



*/