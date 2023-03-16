#include "Renderer.h"

namespace SimulatorCore {
	void Renderer::render(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const {
		vertexArray.bind();
		indexBuffer.bind();
		shader.bind();
		GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, 0));
	}
}


