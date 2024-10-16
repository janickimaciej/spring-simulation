#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	ShaderProgram(const std::string& vertexShaderPath, const std::string& geometryShaderPath,
		const std::string& fragmentShaderPath);
	ShaderProgram(const std::string& vertexShaderPath, const std::string& tessCtrlShaderPath,
		const std::string& tessEvalShaderPath, const std::string& fragmentShaderPath);
	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram(ShaderProgram&&) = delete;
	~ShaderProgram();

	void use() const;

	void setUniform(const std::string& name, bool value) const;
	void setUniform(const std::string& name, int value) const;
	void setUniform(const std::string& name, float value) const;
	void setUniform(const std::string& name, const glm::ivec2& value) const;
	void setUniform(const std::string& name, const glm::vec3& value) const;
	void setUniform(const std::string& name, const glm::mat4& value) const;

private:
	unsigned int m_id{};

	static unsigned int createShader(const std::string& shaderPath, GLenum shaderType);
	static unsigned int createShaderProgram(const std::vector<unsigned int>& shaders);
	static void deleteShaders(const std::vector<unsigned int>& shaders);

	static std::string readShaderFile(const std::string& shaderPath);
	static void printCompilationError(GLenum shaderType, unsigned int shader);
	static void printLinkingError(unsigned int programId);
};
