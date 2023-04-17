#pragma once
#include <string>
#include "GLEW/glew.h"
#include "../Core.h"

namespace SimulatorCore {
	class Texture2D {
	public:
		Texture2D(uint32_t width, uint32_t height);
		Texture2D(const std::string& path);
		~Texture2D();

		uint32_t getWidth() const { return m_Width; }
		uint32_t getHeight() const { return m_Height; }
		uint32_t getRendererID() const { return m_RendererID; }

		const std::string& getPath() const { return m_Path; }

		void setData(void* data, uint32_t size);

		void bind(uint32_t slot = 0) const;

		bool isLoaded() const { return m_IsLoaded; }

		bool operator==(const Texture2D& other) const {
			return m_RendererID == other.getRendererID();
		}
	private:
		std::string m_Path;
		bool m_IsLoaded = false;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;

	};

}

