#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "../Object/Scene.h"

namespace SimulatorCore {
	class Renderer {
	public:
		void render(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
		void render(const Simulator::Scene& scene) const;
		void render(const Simulator::Scene& scene, const Shader& shader) const;
	private:
	};

}

