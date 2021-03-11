#pragma once

// system headers:
#include <string>

class Symbols
{
public:
    static void initSymbols();

    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        static std::wstring getSymbol(std::string const&);
    #else
        static std::string getSymbol(std::string const&);
    #endif
};