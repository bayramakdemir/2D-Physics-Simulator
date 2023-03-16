#include "Core.h"

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* func, const char* file, int line) {
	while (GLenum error = glGetError()) {
		LOG("[OpenGL Error] (" << error << "):" << func <<
			" " << file << ":" << line);
		return false;
	}
	return true;
}

