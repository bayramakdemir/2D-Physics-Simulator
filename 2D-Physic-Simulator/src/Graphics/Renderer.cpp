#include "Renderer.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace SimulatorCore {
	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
	};


	struct RenderData {
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 16;

		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<VertexBuffer> QuadVertexBuffer;
		std::shared_ptr<Shader> QuadShader;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		glm::vec4 QuadVertexPositions[4];

		glm::mat4 viewProjectionMat;
	};

	static RenderData s_Data;


	void Renderer::Init() {

		s_Data.QuadVertexArray = std::make_shared<VertexArray>();
		s_Data.QuadVertexBuffer = std::make_shared<VertexBuffer>(nullptr,s_Data.MaxVertices * sizeof(VertexBuffer));
		SimulatorCore::VertexBufferLayout layout;
		layout.push<float>(3); //positions
		layout.push<float>(4); //color
		s_Data.QuadVertexArray->addBuffer(*s_Data.QuadVertexBuffer.get(), layout);
		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];
		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		std::shared_ptr<IndexBuffer> quadIB = std::make_shared<IndexBuffer>(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->setBuffer(quadIB);
		delete[] quadIndices;

		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		s_Data.QuadShader = std::make_shared<Shader>();
		s_Data.QuadShader->attachShader();

	}

	void Renderer::submit() {
		if (s_Data.QuadIndexCount) {
			uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
			s_Data.QuadVertexBuffer->setData(s_Data.QuadVertexBufferBase, dataSize);

			//TODO: bind texturess

			s_Data.QuadShader->bind();
			s_Data.QuadShader->setUniformMat4f("u_ViewProjection", s_Data.viewProjectionMat);
			drawIndexed(s_Data.QuadVertexArray);
		}
	
	}

	void Renderer::BeginScene(const Simulator::OrthographicCamera& camera) {
		//start render a batch
		s_Data.viewProjectionMat = camera.getViewProjectionMatrix();
		startBatch();
	}

	void Renderer::EndScene() {
		 submit();
	}
	void Renderer::DrawQuad(Simulator::TransformComponent& transform) {
		constexpr size_t quadVertexCount = 4;
		glm::vec4 color = { 0.2+std::rand()/RAND_MAX, 0.2 + std::rand() / RAND_MAX,std::rand()/ RAND_MAX,1.0f };
		for (size_t i = 0; i < quadVertexCount; i++) {
			s_Data.QuadVertexBufferPtr->Position = transform.getTransformationMatrix() * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr++;
		}
		s_Data.QuadIndexCount += 6;
	}

	void Renderer::DrawQuad(const glm::vec3& position) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { 1.0f, 1.0f, 1.0f });
		DrawQuad(transform);
	}

	void Renderer::DrawQuad(const glm::mat4& transform) {
		constexpr size_t quadVertexCount = 4;

		for (size_t i = 0; i < quadVertexCount; i++) {
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = { 1.0f,1.0f,1.0,1.0f };
			s_Data.QuadVertexBufferPtr++;
		}
		s_Data.QuadIndexCount += 6;
	}

	void Renderer::startBatch() {
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}

	void Renderer::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount) {
		vertexArray->bind();
		uint32_t count = indexCount ? indexCount : vertexArray->getIndexBuffer()->getCount();
		GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
	}
}


