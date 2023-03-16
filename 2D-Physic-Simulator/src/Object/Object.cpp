#include "Object.h"
namespace Simulator {

	void Object::setPosition(glm::vec2& position) {
		m_position = position;
	}
	glm::vec2 Object::getPosition() const{
		return m_position;
	}
	void Object::setRotation(glm::vec2& rotation) {
		m_rotation = rotation;
	}
	glm::vec2 Object::getRotation() const {
		return m_rotation;
	}
	void Object::setScale(glm::vec2& scale) {
		m_scale = scale;
	}
	glm::vec2 Object::getScale() const {
		return m_scale;
	}
}