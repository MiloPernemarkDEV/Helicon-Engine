#pragma once

void Handle(const char* expr, const char* msg, const char* file, int line);

#define RT_ASSERT(x, msg) \
        if (!(x)) Handle(#x, msg, __FILE__, __LINE__)


