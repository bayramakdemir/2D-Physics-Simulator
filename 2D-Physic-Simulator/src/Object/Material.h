#pragma once
#include "../Graphics/Shader.h"

namespace Simulator {

	class Material {
	public:

		Material();
		Material(const SimulatorCore::Shader& shader);

		const SimulatorCore::Shader& getShader() {
			return m_shader;
		}
	private:
		SimulatorCore::Shader m_shader;

	};

}