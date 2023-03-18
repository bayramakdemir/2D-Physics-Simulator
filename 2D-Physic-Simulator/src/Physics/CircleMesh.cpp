#include "CircleMesh.h"

namespace Simulator {
	CircleMesh::CircleMesh(const unsigned int vertexCount, float radius): m_vertexCount(vertexCount),m_radius(radius) {
		const float doublePI = 2 * PI;
		float* vertexPositions = new float[m_vertexCount * 3];
		for (int i{ 0 }; i < m_vertexCount; i++) {
			int index = i * 3;
			vertexPositions[index] = m_radius * cos(i * doublePI / m_vertexCount);
			vertexPositions[index + 1] = m_radius * sin(i * doublePI / m_vertexCount);
			vertexPositions[index + 2] = 0.0f;
		}

		m_va.bind();
		SimulatorCore::VertexBuffer vb(vertexPositions, sizeof(float) * 3 * m_vertexCount);
		SimulatorCore::VertexBufferLayout layout;
		layout.push<float>(3);
		m_va.addBuffer(vb, layout);
	
		m_va.unbind();
		vb.unbind();	
		
		delete[] vertexPositions;

	}
	CircleMesh::~CircleMesh() {
	
	}
	void CircleMesh::render() const {
		m_va.bind();
		GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, m_vertexCount));
		m_va.unbind();
	}
}