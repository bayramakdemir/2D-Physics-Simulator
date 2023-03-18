#pragma once
#include "../Graphics/Shader.h"
#include "GameObject.h"
#include "../Physics/CircleMesh.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Simulator {
	class Circle : public GameObject {
	public:
		Circle(float radius)
			:m_radius{ radius }, m_mesh{ CircleMesh(46, 1.0f)}  {

		};
		~Circle() {};

		void setRadius(float r, SimulatorCore::Shader& shader);
		const float getRadius() const;
	private:
		float m_radius;
		Simulator::CircleMesh m_mesh;
	};
}


