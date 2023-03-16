#include "IndexBuffer.h"
#include "../Core.h"

namespace SimulatorCore {
	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):m_count(count) {
		ASSERT(sizeof(unsigned int) == sizeof(GLuint));//unsigned int should be GLuint . carefull!

		GLCall(glGenBuffers(1, &m_rendererID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
		
	}
	IndexBuffer::~IndexBuffer() {
		GLCall(glDeleteBuffers(1, &m_rendererID));
	}
	void IndexBuffer::bind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	}
	void IndexBuffer::unbind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}

