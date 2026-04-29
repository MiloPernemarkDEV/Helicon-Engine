#include "vertex_array.h"

void create_vertex_array_object(VertexArray* vertex_array)
{
	glGenVertexArrays(1, &vertex_array->vertex_array_object);
	glBindVertexArray(vertex_array->vertex_array_object);
}

void bind_vertex_array(VertexArray* vertex_array)
{
	glBindVertexArray(vertex_array->vertex_array_object);
}
