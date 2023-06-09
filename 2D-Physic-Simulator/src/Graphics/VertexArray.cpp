#include "VertexArray.h"
#include "../Core.h"

namespace SimulatorCore {
	VertexArray::VertexArray() {
		GLCall(glGenVertexArrays(1, &m_rendererID));
	}
	VertexArray::~VertexArray() {
		GLCall(glDeleteVertexArrays(1, &m_rendererID));
	}
	void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
		bind();
		vb.bind(); //bind the buffer to vao
		const auto& elements = layout.getElements();
		unsigned int offset{0};
		for (unsigned int i{ 0 }; i < elements.size(); i++) {
			const auto& element = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized,
				layout.getStride(), (const void*) offset));
			//offset must be in bytes. so count * elemtsizeinbytes
			offset += element.count * VertexBufferLayoutElement::getSizeOfType(element.type);
		}
	}

	void VertexArray::setBuffer(std::shared_ptr<IndexBuffer>& buffer) {
		buffer->bind();
		m_indexBuffer = buffer;
	}

	void VertexArray::bind() const {
		GLCall(glBindVertexArray(m_rendererID));
	}
	void VertexArray::unbind() const {
		GLCall(glBindVertexArray(0));
	}
}