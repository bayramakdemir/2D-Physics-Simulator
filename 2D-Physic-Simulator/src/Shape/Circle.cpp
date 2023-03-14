#include "GLEW/glew.h"
#include "Circle.h"
#include <math.h>

namespace Simulator {
	void Circle::render() {

		float x{ 0.1f }, y{ 0.1f }, PI{ 3.14159265f }, radius{0.4f};
		int i;
		int triangleAmount = 100; //# of triangles used to draw circle

		//GLfloat radius = 0.8f; //radius
		GLfloat twicePi = 2.0f * PI;

		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for (i = 0; i <= triangleAmount;i++) {
			glVertex2f(
				x + (radius * cos(i * twicePi / triangleAmount)),
				y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
		glEnd();
	}
}