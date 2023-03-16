#include "RectangleMesh.h"

namespace Simulator {
	RectangleMesh::RectangleMesh(const glm::vec2* vertices) {
		if (&vertices[2] != nullptr)
			m_scale = { vertices[2].x,-vertices[2].y };
	}
}
