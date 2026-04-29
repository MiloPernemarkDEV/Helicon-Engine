#pragma once
#include "engine_assert.h"
#include <memory>
#include <new> 
#include <iostream>

struct Arena {
    char* buffer = nullptr;
    size_t current_position = 0;  
    size_t total_size = 0; 
};

void engine_create_arena(Arena* arena);
void engine_destroy_arena(Arena* arena);

template<typename T>
T* engine_allocate(Arena* arena) {
    size_t size = sizeof(T);
    size_t alignment = alignof(T);

    void* start_ptr = static_cast<void*>(arena->buffer + arena->current_position);

    void* aligned_ptr = start_ptr;
    size_t space = arena->total_size - arena->current_position;

    if (std::align(alignment, size, aligned_ptr, space)) {

        size_t padding = reinterpret_cast<uintptr_t>(aligned_ptr) -
            reinterpret_cast<uintptr_t>(start_ptr);

        arena->current_position += padding + size;

        return new (aligned_ptr) T();
    }

    RT_ASSERT(false, "Arena is full or alignment failed!");
    return nullptr;
}

inline void engine_reset_arena(Arena* arena) {
    RT_ASSERT(arena != nullptr, "Cannot reset a null arena!");
    arena->current_position = 0;
}