#include "TransformComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Simulator {
	TransformComponent::TransformComponent()
	:m_position({0.0f,0.0f,0.0f}), m_rotation({ 0.0f,0.0f,0.0f }),m_scale({ 1.0f,1.0f,1.0f }) {
		
	}
	void TransformComponent::setPosition(const glm::vec3& position) {
		m_position = position;
	}
	void TransformComponent::setRotation(const glm::vec3& rotation) {
		m_rotation = rotation;
	}
	void TransformComponent::setScale(const glm::vec3& scale) {
		m_scale = scale;
	}
	
	const glm::vec3& TransformComponent::getPosition() const {
		return m_position;
	}
	const glm::vec3& TransformComponent::getRotation() const {
		return m_rotation;
	}
	const glm::vec3& TransformComponent::getScale() const {
		return m_scale;
	}
	const glm::mat4 TransformComponent::getTransformationMatrix() const{
		glm::mat4 rotation = glm::toMat4(glm::quat(m_rotation));

		return glm::translate(glm::mat4(1.0f), m_position)
			* rotation
			* glm::scale(glm::mat4(1.0f), m_scale);
	}
}
