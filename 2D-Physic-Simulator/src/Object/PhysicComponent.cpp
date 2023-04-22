#include "PhysicComponent.h"

namespace Simulator {

	CircleRigidbody::CircleRigidbody(TransformComponent* transform) {
		m_transform = transform;
		m_positionLast = transform->getPosition();
		m_acceleration = {};
	}
	void CircleRigidbody::accelerate(const glm::vec2& acceleration) {
		m_acceleration += acceleration;
	}

	void CircleRigidbody::setVelocity(const glm::vec2& velocity, float dt) {
		m_positionLast = glm::vec2(m_transform->getPosition()) - (velocity * dt);
	}

	void CircleRigidbody::addVelocity(const glm::vec2& velocity, float dt) {
		m_positionLast -= velocity * dt;
	}

	const glm::vec2& CircleRigidbody::getVelocity(float dt) const {
		return (glm::vec2(m_transform->getPosition()) - m_positionLast) / dt;
	}

	void CircleRigidbody::step(float dt) {
		const glm::vec2 position = glm::vec2(m_transform->getPosition());
		const glm::vec2 displacement = position - m_positionLast;
		
		m_positionLast = position;
		m_transform->setPosition({ position + displacement + m_acceleration * (dt * dt), 0.0f });
	
		m_acceleration = {};
	}
}