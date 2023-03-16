#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace SimulatorCore {
	class Renderer {
	public:
		void render(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
	private:
	};

}

