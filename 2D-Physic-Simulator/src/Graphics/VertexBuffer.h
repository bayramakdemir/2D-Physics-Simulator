#pragma once
#include <stdint.h>
namespace SimulatorCore {
	class VertexBuffer {
	public:
		//size means how many bytes the data has
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void bind() const;
		void unbind() const;
		void setData(const void* data, uint32_t size);
	private:
		//internal renderer id, generic
		unsigned int m_rendererID;
	};
}



