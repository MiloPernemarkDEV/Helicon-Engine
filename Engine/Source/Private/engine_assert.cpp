#include "engine_assert.h"
#include <iostream>

void Handle(const char* expr,
    const char* msg,
    const char* file,   
    int line)
{
    std::cerr << "========================================\n";
    std::cerr << "TEIDE ASSERTION FAILED\n";
    std::cerr << "Expression: " << expr << "\n";

    if (msg)
        std::cerr << "Message: " << msg << "\n";

    std::cerr << "File: " << file << "\n";
    std::cerr << "Line: " << line << "\n";
    std::cerr << "========================================\n";

#if defined(_MSC_VER)
        __debugbreak();
#else
    std::abort();
#endif
}