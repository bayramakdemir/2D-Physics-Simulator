#pragma once
#include "glm/vec4.hpp"

namespace Simulator {
	struct CircleRendererComponent {
		glm::vec4 color = {1.0f,1.0f,1.0f,1.0f};
		float thickness = { 1.0f };
		float fade = { 0.005f };
	};
}