#pragma once
#include <GLEW/glew.h>
#include <cmath>
#include "../Graphics/VertexArray.h"
#include "../Graphics/VertexBuffer.h"

namespace Simulator {
	constexpr float PI = 3.14159265359f;
	class CircleMesh {
	public:
		CircleMesh(const unsigned int vertexCount, float radius);
		~CircleMesh();

		void render() const;
	private:
		unsigned int m_vertexCount;
		float m_radius;
		SimulatorCore::VertexArray m_va;
	};

}

