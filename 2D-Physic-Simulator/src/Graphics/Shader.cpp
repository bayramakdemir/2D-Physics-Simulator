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
		if (data == "") {
			LOG("Shader not found. Please check the path or name")
		}
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

		
		shader = glCreateShader(shadertype);
		glShaderSource(shader, 1, &text, NULL);
		glCompileShader(shader);
		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
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
			LOG("Vertex Shader not found. Defealt vs will be used.");
			compileShaderFromFile("../assets/shaders/VertexShader.vs", Shader::VERTEX);
		}
		if (m_shaders[1] == 0) {
			LOG("Fragment Shader not found. Defealt fs will be used.");
			compileShaderFromFile("../assets/shaders/FragmentShader.fs", Shader::FRAGMENT);
		}
		
		glAttachShader(m_program, m_shaders[0]);
		glAttachShader(m_program, m_shaders[1]);
		glLinkProgram(m_program);

		int success;
		glGetProgramiv(m_program, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetProgramInfoLog(m_program, 512, NULL, infoLog);
			LOG("ERROR SHADER LINKING FAILED:" << infoLog);
		}

		glDeleteShader(m_shaders[0]);
		glDeleteShader(m_shaders[1]);
	}
	void Shader::useShader() {
		//better to call validate before every draw call for checking. can be reomved in the future
		//glValidateProgram(m_program);
		glUseProgram(m_program);
	}


	void Shader::registerUniformLocation(const char* name) {
		m_uniformLocations[name] = glGetAttribLocation(m_program, name);
	}
	void Shader::setUniform(const char* name, float x, float y, float z) {

		glVertexAttribPointer(m_uniformLocations[name], 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
	void Shader::setUniform(const char* name, glm::vec2& v) {

	}


	void Shader::dispose() {
		glDeleteProgram(m_program);
	}
}
