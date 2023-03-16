#pragma once

namespace SimulatorCore {
	class IndexBuffer {
	public:
		//count is element count
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;
		inline unsigned int getCount() const { return m_count; }
	private:
		//internal renderer id, generic
		unsigned int m_rendererID;
		unsigned int m_count; //how many indices we have
	};
}



