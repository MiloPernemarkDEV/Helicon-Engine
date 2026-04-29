#pragma once

#include <glad/glad.h> 

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

struct shader {
	const char* vertexPath;
	const char* fragmentPath;
	GLuint ID; 
};

bool shader_create(shader* shader);
void shader_use(shader* shader);

void shader_set_bool(shader* shader, const std::string& name, bool value);
void shader_set_int(shader* shader, const std::string& name, int value);
void shader_set_float(shader* shader, const std::string& name, float value);



