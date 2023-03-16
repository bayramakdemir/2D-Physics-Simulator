#pragma once
#include "glm/vec2.hpp"
namespace Simulator {
	class Object {
	public:
		virtual void render() const = 0;
		Object() :m_position({ 0,0 }), m_scale({ 1,1 }), m_rotation({ 0,0 }) {};

		glm::vec2 getPosition() const;
		void setPosition(glm::vec2& position);
		glm::vec2 getRotation() const;
		void setRotation(glm::vec2& rotation);
		glm::vec2 getScale() const;
		void setScale(glm::vec2& scale);
	protected:
		glm::vec2 m_rotation;
		glm::vec2 m_position;
		glm::vec2 m_scale;
	};
}


