#pragma once
#include "glm/vec3.hpp"
#include "../Graphics/Shader.h"

namespace Simulator {
	struct TransformComponent {
	public:
		TransformComponent();

		void setPosition(const glm::vec3& position);
		void setRotation(const glm::vec3& rotation);
		void setScale(const glm::vec3& scale);

		const glm::vec3& getPosition() const;
		const glm::vec3& getRotation() const;
		const glm::mat4& getTransformationMatrix() const;
		const glm::vec3& getScale() const;

	private:
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
	};

}

