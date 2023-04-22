#pragma once
#include "TransformComponent.h"
#include "glm/glm.hpp"

namespace Simulator {
	class CircleRigidbody {
	public:
		CircleRigidbody() = delete;
		CircleRigidbody(TransformComponent* transform);

		void accelerate(const glm::vec2& acceleration);
		void setVelocity(const glm::vec2& velocity, float dt);
		void addVelocity(const glm::vec2& velocity, float dt);

		void step(float dt);
		const glm::vec2& getVelocity(float dt) const;

	private:
		float m_mass;
		glm::vec2 m_acceleration;
		glm::vec2 m_positionLast;
		TransformComponent* m_transform;
	};
}