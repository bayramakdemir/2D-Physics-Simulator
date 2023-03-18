#include "Material.h"

namespace Simulator {
	Material::Material() {
		//assign default shader
	}
	Material::Material(const SimulatorCore::Shader& shader) {
		m_shader = shader;
	}

}