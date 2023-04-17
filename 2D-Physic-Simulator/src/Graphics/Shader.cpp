#include "Shader.h"
#include "../Core.h"
#include <string>
#include <fstream>

namespace SimulatorCore {

	void Shader::compileShaderFromFile(const char* filename, ShaderType type) {
		std::string line, text;
		std::ifstream in(filename);
		while (std::getline(in, line)) {
			text += line + "\n";
		}
		const char* data = text.c_str();
		ASSERT(text != "");
		compileShaderFromText(data, type);
	}
	void Shader::compileShaderFromText(const char* text, ShaderType type) {
		unsigned int shader;
		unsigned int shadertype = 0;
		switch (type) {
		case Shader::VERTEX:
			shadertype = GL_VERTEX_SHADER;
			break;
		case Shader::FRAGMENT:
			shadertype = GL_FRAGMENT_SHADER;;
			break;
		default:
			break;
		}
		GLCall(shader = glCreateShader(shadertype));
		GLCall(glShaderSource(shader, 1, &text, NULL));
		GLCall(glCompileShader(shader));
		int success;
		GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
		if (!success) {
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			LOG("ERROR SHADER COMPILATION_FAILED:" << type << " More:"<< infoLog);
			return;
		}
		m_shaders[type] = shader;
	}

	void Shader::attachShader() {
		if (m_shaders[0] == 0) {
			LOG("Vertex Shader not found. Default vs will be used.");
			compileShaderFromFile("../res/shaders/VertexShader.glsl", Shader::VERTEX);
		}
		if (m_shaders[1] == 0) {
			LOG("Fragment Shader not found. Default fs will be used.");
			compileShaderFromFile("../res/shaders/FragmentShader.glsl", Shader::FRAGMENT);
		}
		

		GLCall(m_program = glCreateProgram());
		GLCall(glAttachShader(m_program, m_shaders[0]));
		GLCall(glAttachShader(m_program, m_shaders[1]));
		GLCall(glLinkProgram(m_program));
		GLCall(glValidateProgram(m_program));

		int success;
		GLCall(glGetProgramiv(m_program, GL_LINK_STATUS, &success));
		if (!success) {
			char infoLog[512];
			glGetProgramInfoLog(m_program, 512, NULL, infoLog);
			LOG("ERROR SHADER LINKING FAILED:" << infoLog);
		}

		GLCall(glDeleteShader(m_shaders[0]));
		GLCall(glDeleteShader(m_shaders[1]));
	}

	void Shader::bind() const {
		GLCall(glUseProgram(m_program));
	}
	void Shader::unbind() const {
		GLCall(glUseProgram(0));
	}

	void Shader::setUniform4f(const std::string& name,const glm::vec4& v) {
		GLCall(glUniform4f(getUniformLocation(name),v.x,v.y,v.z,v.w));
	}

	void Shader::setUniform3f(const std::string& name,const glm::vec3& v) {
		GLCall(glUniform3f(getUniformLocation(name), v.x, v.y, v.z));
	}

	void Shader::setUniform2f(const std::string& name,const glm::vec2& v) {
		GLCall(glUniform2f(getUniformLocation(name), v.x, v.y));
	}

	void Shader::setUniform1f(const std::string& name,const float v) {
		GLCall(glUniform1f(getUniformLocation(name),v));
	}

	void Shader::setUniformMat4f(const std::string& name,const glm::mat4& v) {
		
		GLCall(glUniformMatrix4fv(getUniformLocation(name),1,GL_FALSE, &v[0][0]));
	}


	int Shader::getUniformLocation(const std::string& name) {
		if (m_uniformLocations.find(name) != m_uniformLocations.end())
			return m_uniformLocations[name];

		GLCall(int location = glGetUniformLocation(m_program, name.c_str()));
		if (location == -1) {
			LOG("Warning: Uniform " << name << "doesnt exist or not used in shader.");
		}
		m_uniformLocations[name] = location;
		return location;
	}

	void Shader::dispose() {
		GLCall(glDeleteProgram(m_program));
	}
}
