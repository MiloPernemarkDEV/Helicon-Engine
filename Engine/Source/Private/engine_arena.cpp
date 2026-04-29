#include "engine_arena.h"
#include <iostream>


void engine_create_arena(Arena* arena) {
    RT_ASSERT(arena != nullptr, "Arena pointer is null!");
    arena->current_position = 0;

    arena->buffer = static_cast<char*>(::operator new(arena->total_size));
}

void engine_destroy_arena(Arena* arena) {
    if (arena->buffer) {
        ::operator delete(arena->buffer);

        arena->buffer = nullptr;
        arena->total_size = 0;
        arena->current_position = 0;
    }
}