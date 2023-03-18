#pragma once
#include "glm/vec3.hpp"

namespace Simulator {
	class Transform {
	public:
		void setPosition(const glm::vec3& position);
		void setRotation(const glm::vec3& rotation);
		void setScale(const glm::vec3& scale);
		void move(const glm::vec3& move_amount);
		void rotate(const float angle, const glm::vec3& axis);
		void scale(const glm::vec3& scale);
		const glm::vec3& getPosition() const;
		const glm::vec3& getRotation() const;
		const glm::vec3& getScale() const;
	private:
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
	};

}

