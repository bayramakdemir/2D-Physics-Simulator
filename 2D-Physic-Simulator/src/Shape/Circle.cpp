#include "GLEW/glew.h"
#include "Circle.h"
#include <math.h>

namespace Simulator {
	void Circle::render() const {

		float PI{ 3.14159265f }, radius{100.0f};
		int i;
		int triangleAmount = 100; //# of triangles used to draw circle

		//GLfloat radius = 0.8f; //radius
		GLfloat twicePi = 2.0f * PI;

		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(m_position.x, m_position.y); // center of circle
		for (i = 0; i <= triangleAmount;i++) {
			glVertex2f(
				m_position.x + (radius * cos(i * twicePi / triangleAmount)),
				m_position.y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
		
		glEnd();
	}

	void Circle::setRadius(float radius) {
		m_radius = radius;
	}
	float Circle::getRadius() const{
		return m_radius;
	}
}