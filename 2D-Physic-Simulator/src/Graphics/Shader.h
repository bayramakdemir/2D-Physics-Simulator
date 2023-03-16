#pragma once
#include "GLEW/glew.h"
#include <map>
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

		void registerUniformLocation(const char* name);

		void setUniform(const char* name, float x, float y, float z);
		void setUniform(const char* name, glm::vec2& v);
	


		void attachShader();
		void useShader();

	private:
		unsigned int m_program;
		unsigned int m_shaders[2];
		unsigned int m_count;
		std::map<std::string, int> m_uniformLocations;
		
		void dispose();
	};
}


