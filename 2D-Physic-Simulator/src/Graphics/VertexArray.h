#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
namespace SimulatorCore {
	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
		std::shared_ptr<IndexBuffer> getIndexBuffer() const{ return m_indexBuffer; }
		void setBuffer(std::shared_ptr<IndexBuffer>& buffer);
		void bind() const;
		void unbind() const;

	private:
		unsigned int m_rendererID;
		std::shared_ptr<IndexBuffer> m_indexBuffer;
	};
}


