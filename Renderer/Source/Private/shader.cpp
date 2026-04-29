#include "shader.h"
#include <filesystem>

bool shader_create(shader* shader)
{
    std::cerr << "WORKING DIR: "
          << std::filesystem::current_path() << std::endl;
    
	std::string	vertex_code;
	std::string fragment_code;
	std::ifstream v_shader_file;
	std::ifstream f_shader_file;

	v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
        v_shader_file.open("shader.vert");
        f_shader_file.open("shader.frag");
        std::stringstream v_shader_stream, f_shader_stream;
        // read file's buffer contents into streams
        v_shader_stream << v_shader_file.rdbuf();
        f_shader_stream << f_shader_file.rdbuf();
        // close file handlers
        v_shader_file.close();
        f_shader_file.close();
        // convert stream into string
        vertex_code = v_shader_stream.str();
        fragment_code = f_shader_stream.str();
	    std::cout << "Read file successfully" << std::endl;
	}
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n";
        return false; 
    }

    const char* v_shader_code = vertex_code.c_str();
    const char* f_shader_code = fragment_code.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &v_shader_code, nullptr);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &f_shader_code, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    shader->ID = glCreateProgram();
    glAttachShader(shader->ID, vertex);
    glAttachShader(shader->ID, fragment);
    glLinkProgram(shader->ID);
    // print linking errors if any
    glGetProgramiv(shader->ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader->ID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    return true;
}

void shader_use(shader* shader)
{
    glUseProgram(shader->ID);
}

void shader_set_bool(shader* shader, const std::string& name, bool value)
{
    if (!shader) {
        throw std::runtime_error("ERROR::PASSED_NULLPTR");
    }
    glUniform1i(glGetUniformLocation(shader->ID, name.c_str()), (int)value);
}

void shader_set_int(shader* shader, const std::string& name, int value)
{
    if (!shader) {
        throw std::runtime_error("ERROR::PASSED_NULLPTR");
    }
    glUniform1i(glGetUniformLocation(shader->ID, name.c_str()), value);
}

void shader_set_float(shader* shader, const std::string& name, float value)
{
    if (!shader) {
        throw std::runtime_error("ERROR::PASSED_NULLPTR");
    }
    glUniform1f(glGetUniformLocation(shader->ID, name.c_str()), value);

}
