#pragma once
#include "GLEW/glew.h"
#include <unordered_map>
#include <string>
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"

namespace SimulatorCore {
	class Shader {
	public:

		enum ShaderType {
			VERTEX = 0,
			FRAGMENT = 1
		};

		Shader() :m_count(0), m_shaders{ 0,0 }, m_program(glCreateProgram()) {};
		~Shader() { dispose(); };

		void compileShaderFromFile(const char* filename, ShaderType type);
		void compileShaderFromText(const char* text, ShaderType type);

		void setUniform4f(const std::string& name, glm::vec4& v);
		void setUniform3f(const std::string& name, glm::vec3& v);
		void setUniform2f(const std::string& name, glm::vec2& v);
	
		void attachShader();
		void bind() const;
		void unbind() const;
	private:
		unsigned int m_program;
		unsigned int m_shaders[2];
		unsigned int m_count;
		std::unordered_map<std::string, int> m_uniformLocations;
		
		int getUniformLocation(const std::string& location);
		void dispose();
	};
}


