#pragma once

#include <glad/glad.h>

struct VertexArray {
	GLuint vertex_array_object;
};

void create_vertex_array_object(VertexArray* vertex_array);
void bind_vertex_array(VertexArray* vertex_array);