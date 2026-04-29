#pragma once

#include <glad/glad.h>
#include <vector>

struct Vertex;

struct VertexBuffer
{
	GLuint vertex_buffer_object;
};

void create_vertex_buffer(VertexBuffer* vertex_buffer);
void bind_vertex_buffer(VertexBuffer* vertex_buffer);
void add_data_vertex_buffer(VertexBuffer* vertex_buffer, const void* data, std::size_t size);