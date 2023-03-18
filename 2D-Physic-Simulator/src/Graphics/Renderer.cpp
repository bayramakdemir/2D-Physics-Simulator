#include "Renderer.h"

namespace SimulatorCore {
	void Renderer::render(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const {
		vertexArray.bind();
		indexBuffer.bind();
		shader.bind();
		GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, 0));
	}
	void Renderer::render(const Simulator::Scene& scene) const {
		scene.render();
	}
	void Renderer::render(const Simulator::Scene& scene, const Shader& shader) const {
		shader.bind();
		scene.render();
		shader.unbind();
	}
}


