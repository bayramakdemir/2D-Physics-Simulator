#include "OrthographicCamera.h"
#include "glm/gtx/transform.hpp"
#include <iostream>

namespace Simulator {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) 
	:m_projectionMatrix(glm::ortho(left,right,bottom, top, -1.0f, 1.0f)), m_viewMatrix(1.0f),m_zoom_level(1.0f),
		m_boundry( left,right,bottom, top )
	{
		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
		
	}

	void OrthographicCamera::setProjection(float left, float right, float bottom, float top) {
		m_boundry = { left, right, bottom, top };
		m_projectionMatrix = glm::ortho(m_boundry.x * m_zoom_level, m_boundry.y * m_zoom_level, m_boundry.z * m_zoom_level, m_boundry.w * m_zoom_level, -1.0f, 1.0f);
		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
		
	}

	void OrthographicCamera::recalculateViewMatrix() {
	
		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), m_position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));

		m_viewMatrix = glm::inverse(Transform);
		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void OrthographicCamera::zoom(float zoom) {
		if (zoom) {
			m_zoom_level += zoom;
			m_projectionMatrix = glm::ortho(m_boundry.x * m_zoom_level, m_boundry.y * m_zoom_level, m_boundry.z * m_zoom_level, m_boundry.w * m_zoom_level, -1.0f, 1.0f);
			m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
		}
		
	}

	const glm::vec2 OrthographicCamera::screenToWorldCoord(const glm::vec2& point, const glm::vec2& screen_size) {
		glm::mat4 inverse_viewprojection = glm::inverse(m_viewProjectionMatrix);
	
		float x_ndc = (2.0f * point.x) / screen_size.x - 1.0f;
		float y_ndc = 1.0f - (2.0f * point.y) / screen_size.y;

		glm::vec4 ndc_p = glm::vec4(x_ndc, y_ndc, 0.0f, 1.0f);
		glm::vec4 cam_p = inverse_viewprojection * ndc_p;
		cam_p /= cam_p.w;

		const glm::vec2 world_p = glm::vec2(cam_p.x,cam_p.y);
		return world_p;
	}
}