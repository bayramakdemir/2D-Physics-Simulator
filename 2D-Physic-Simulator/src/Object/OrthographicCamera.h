#pragma once
#include "glm/glm.hpp"
#include "TransformComponent.h"
namespace Simulator {

	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		~OrthographicCamera();

		void recalculateViewMatrix();

		void setProjection(float left, float right, float bottom, float top);

		const glm::vec3& getPosition() const { return m_position; }
		void setPosition(const glm::vec3& position) { m_position = position; recalculateViewMatrix(); }

		float getRotation() const { return m_rotation; }
		void setRotation(float rotation) { m_rotation = rotation; recalculateViewMatrix(); }

		void move(const glm::vec3& move_amount){
			m_position += move_amount;
			recalculateViewMatrix();
		};

		void zoom(float zoom);

		const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }
		const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
		const glm::mat4& getViewProjectionMatrix() const { return m_viewProjectionMatrix; }
		const glm::vec2 screenToWorldCoord(const glm::vec2& point, const glm::vec2& screen_size);

	protected:
		glm::mat4 m_viewProjectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;

		glm::vec4 m_boundry;
		float m_zoom_level;

		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
		float m_rotation = 0.0f;
	};

}

