#include "GLEW/glew.h"
#include "Circle.h"
#include <math.h>

namespace Simulator {
	/*void Circle::render() const {

		m_mesh.render();
	}*/

	void Circle::setRadius(float radius,SimulatorCore::Shader& shader) {
		m_radius = radius;
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(radius, radius, 1.0f));
		shader.bind(); 
		shader.setUniformMat4f("u_Model", scale);
		shader.unbind();
	}
	const float Circle::getRadius() const{
		return m_radius;
	}
}