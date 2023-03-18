#include "Transform.h"

namespace Simulator {
	void Transform::setPosition(const glm::vec3& position) {
		m_position = position;
	}
	void Transform::setRotation(const glm::vec3& rotation) {
		m_rotation = rotation;
	}
	void Transform::setScale(const glm::vec3& scale) {
		m_scale = scale;
	}
	void Transform::move(const glm::vec3& move_amount) {
		m_position += move_amount;
	}

	void Transform::rotate(const float angle, const glm::vec3& axis) {
		
	}
	void Transform::scale(const glm::vec3& scale) {
	}
	const glm::vec3& Transform::getPosition() const {
		return m_position;
	}
	const glm::vec3& Transform::getRotation() const {
		return m_rotation;
	}
	const glm::vec3& Transform::getScale() const {
		return m_scale;
	}
}
