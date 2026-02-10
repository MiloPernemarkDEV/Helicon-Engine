
// Shader.h

#pragma once
#include <glad/glad.h>
#include <string>
#include <unordered_map>

namespace Helicon 
{
	class Shader
	{

	public:

		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		void bind() const; 
		void unBind() const; 

		void setUniformInt(const std::string& name, int value);
		void setUniformFloat4(const std::string& name, float v1, float v2, float v3, float v4);

		int GetUniformLocation(const std::string& name) const;

	private:

		mutable std::unordered_map<std::string, int> m_UniformLocationCache;
		uint32_t m_RendererID;
		std::string readFile(const std::string& filePath);
		uint32_t compileShader(uint32_t type, const std::string& source);
	};
}


