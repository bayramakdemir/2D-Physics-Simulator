#pragma once
#include "GLEW/glew.h"
#include <unordered_map>
#include <string>
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"

namespace SimulatorCore {
	class Shader {
	public:
		static Shader DefaultShader;

		enum ShaderType {
			VERTEX = 0,
			FRAGMENT = 1
		};

		Shader() : m_shaders{ 0,0 }, m_program(0) {};
		~Shader() { dispose(); };

		void compileShaderFromFile(const char* filename, ShaderType type);
		void compileShaderFromText(const char* text, ShaderType type);

		void setUniform4f(const std::string& name, glm::vec4& v);
		void setUniform3f(const std::string& name, glm::vec3& v);
		void setUniform2f(const std::string& name, glm::vec2& v);

		void setUniformMat4f(const std::string& name, glm::mat4& v);
	
		void attachShader();
		void bind() const;
		void unbind() const;

		const unsigned int getProgramId() const{
			return m_program;
		}
	private:
		unsigned int m_program;
		unsigned int m_shaders[2];

		std::unordered_map<std::string, int> m_uniformLocations;
		
		int getUniformLocation(const std::string& location);
		void dispose();
	};
}


