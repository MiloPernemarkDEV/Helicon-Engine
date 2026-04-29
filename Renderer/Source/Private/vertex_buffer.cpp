#include "vertex_buffer.h"

#include <iostream>

void create_vertex_buffer(VertexBuffer* vertex_buffer)
{
	glGenBuffers(1, &vertex_buffer->vertex_buffer_object);
}

void bind_vertex_buffer(VertexBuffer* vertex_buffer)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->vertex_buffer_object);
}

void add_data_vertex_buffer(VertexBuffer* vertex_buffer, const void* data, std::size_t size)
{
	if (!data) {
		return;
	}
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
