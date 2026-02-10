
#include "Shader.h"

#include "../core/logger.h"
#include <fstream>
#include <sstream>

// Going to go over this class 100 times until i fully understand it 
// the basic idea is to load a a shader file from disk that has the vertex and fragment source code 
// compile the source code so the gpu can understand it, store it in memory and use the id to say hey here it is stupid gpu 
// the rest is not in my head rn but ill update this documentation 
// basically openGL got us covered for the most part here 

using namespace Helicon;

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	uint32_t vs = compileShader(GL_VERTEX_SHADER, readFile(vertexPath));
	uint32_t fs = compileShader(GL_FRAGMENT_SHADER, readFile(fragmentPath));

	m_RendererID = glCreateProgram();
	glAttachShader(m_RendererID, vs);
	glAttachShader(m_RendererID, fs);
	glLinkProgram(m_RendererID);

	int isLinked = 0;
	glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);

	if (isLinked == GL_FALSE)
	{
		HEL_ERROR("Shader Linking Failed: {0}");
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::unBind() const
{
	glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string& name) const
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
		HEL_WARN("Uniform not found!");

	m_UniformLocationCache[name] = location;
	return location;
}

void Shader::setUniformInt(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::setUniformFloat4(const std::string& name, float v1, float v2, float v3, float v4)
{
	glUniform4f(GetUniformLocation(name), v1, v2, v3, v4);
}

std::string Shader::readFile(const std::string& filePath)
{
	std::string result;
	std::ifstream in(filePath, std::ios::in | std::ios::binary);
	
	if (in) 
	{
		std::stringstream ss;
		ss << in.rdbuf(); 
		result = ss.str();
	}
	else 
	{
		HEL_ERROR("Could not open shader file: ");
	}

	return result;
}

uint32_t Shader::compileShader(uint32_t type, const std::string& source)
{
	uint32_t id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	
	if (result == GL_FALSE)
	{
		HEL_ERROR("Failed to compile {0} shader: {1}");

		glDeleteShader(id);
		return 0;
	}

	return id;
}
