#pragma once
#include "Mesh.h"
#include "glm/vec2.hpp"

namespace Simulator {

	class RectangleMesh: public Mesh {
	public:
		RectangleMesh() :m_vertices{ { 0,0 },{1,0}, { 1,-1 }, { 0,-1 } }, m_scale({1,1}) {};
		RectangleMesh(const glm::vec2* vertices);
		RectangleMesh(glm::vec2& scale):m_scale(scale){
			m_vertices[0] = { 0,0 };
			m_vertices[1] = { scale.x,0 };
			m_vertices[2] = { scale.x, -scale.y };
			m_vertices[3] = { 0,-scale.y };
		};
	private:
		//vertices in clockwise, first vertex at the top left corner
		glm::vec2 m_vertices[4]; 
		glm::vec2 m_scale;
	};


}
