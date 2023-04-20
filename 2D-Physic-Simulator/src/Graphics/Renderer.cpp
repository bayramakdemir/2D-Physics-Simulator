#include "Renderer.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace SimulatorCore {
	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
	};
	struct CircleVertex {
		glm::vec3 WorldPosition;
		glm::vec3 LocalPosition;
		glm::vec4 Color;
		float Thickness;
		float Fade;
	};

	struct RenderData {
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 16;

		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<VertexBuffer> QuadVertexBuffer;
		std::shared_ptr<Shader> QuadShader;

		std::shared_ptr<VertexArray> CircleVertexArray;
		std::shared_ptr<VertexBuffer>  CircleVertexBuffer;
		std::shared_ptr<Shader> CircleShader;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		uint32_t CircleIndexCount = 0;
		CircleVertex* CircleVertexBufferBase = nullptr;
		CircleVertex* CircleVertexBufferPtr = nullptr;

		glm::vec4 QuadVertexPositions[4];
		glm::mat4 viewProjectionMat;
	};

	static RenderData s_Data;
	Renderer::RenderStats Renderer::RenderStat = { 0,0 };
	bool Renderer::isRendering = false;

	uint32_t drawnTriangles = 0;
	void Renderer::Init() {
		//QUAD 
		s_Data.QuadVertexArray = std::make_shared<VertexArray>();
		s_Data.QuadVertexBuffer = std::make_shared<VertexBuffer>(nullptr,s_Data.MaxVertices * sizeof(QuadVertex));
		SimulatorCore::VertexBufferLayout quadlayout;
		quadlayout.push<float>(3); //positions
		quadlayout.push<float>(4); //color
		s_Data.QuadVertexArray->addBuffer(*s_Data.QuadVertexBuffer.get(), quadlayout);
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

		//CIRCLE
		s_Data.CircleVertexArray = std::make_shared<VertexArray>();
		s_Data.CircleVertexBuffer = std::make_shared<VertexBuffer>(nullptr, s_Data.MaxVertices * sizeof(CircleVertex));
		SimulatorCore::VertexBufferLayout circlelayout;

		circlelayout.push<float>(3); //WorldPosition
		circlelayout.push<float>(3); //LocalPosition
		circlelayout.push<float>(4); //color
		circlelayout.push<float>(1); //thickness
		circlelayout.push<float>(1); //fade

		s_Data.CircleVertexArray->addBuffer(*s_Data.CircleVertexBuffer.get(), circlelayout);
		s_Data.CircleVertexArray->setBuffer(quadIB);

		s_Data.CircleVertexBufferBase = new CircleVertex[s_Data.MaxVertices];

		s_Data.CircleShader = std::make_shared<Shader>();
		s_Data.CircleShader->compileShaderFromFile("../res/shaders/Circle_vertex_shader.glsl", SimulatorCore::Shader::VERTEX);
		s_Data.CircleShader->compileShaderFromFile("../res/shaders/Circle_fragment_shader.glsl", SimulatorCore::Shader::FRAGMENT);
		s_Data.CircleShader->attachShader();

	}

	void Renderer::submit() {
		if (s_Data.QuadIndexCount) {
			uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
			s_Data.QuadVertexBuffer->setData(s_Data.QuadVertexBufferBase, dataSize);

			//TODO: bind textures

			s_Data.QuadShader->bind();
			s_Data.QuadShader->setUniformMat4f("u_ViewProjection", s_Data.viewProjectionMat);
			drawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
			RenderStat.RenderCall++;
		}
		if (s_Data.CircleIndexCount) {
			uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.CircleVertexBufferPtr - (uint8_t*)s_Data.CircleVertexBufferBase);
			s_Data.CircleVertexBuffer->setData(s_Data.CircleVertexBufferBase, dataSize);

			//TODO: bind textures

			s_Data.CircleShader->bind();
			s_Data.CircleShader->setUniformMat4f("u_ViewProjection", s_Data.viewProjectionMat);
			drawIndexed(s_Data.CircleVertexArray, s_Data.CircleIndexCount);
			RenderStat.RenderCall++;
		}
	}

	void Renderer::BeginScene(const Simulator::OrthographicCamera& camera) {
		//start render a batch
		isRendering = true;
		s_Data.viewProjectionMat = camera.getViewProjectionMatrix();
		RenderStat.RenderCall = 0;
		RenderStat.TriangleCount = 0;
		
		startBatch();
	}

	void Renderer::EndScene() {
		 submit();
		 isRendering = false;
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
		RenderStat.TriangleCount += 2;
		drawnTriangles += 2;
	}

	void Renderer::DrawCircle(const glm::mat4& transform, const Simulator::CircleRendererComponent& circleRenderer) {
		if (drawnTriangles > s_Data.MaxVertices / 3) {
			nextBatch();
		}

		constexpr size_t quadVertexCount = 4;
		for (size_t i = 0; i < quadVertexCount; i++) {
			s_Data.CircleVertexBufferPtr->WorldPosition = transform * s_Data.QuadVertexPositions[i];
			s_Data.CircleVertexBufferPtr->LocalPosition = s_Data.QuadVertexPositions[i] * 2.0f;
			s_Data.CircleVertexBufferPtr->Color = circleRenderer.color;
			s_Data.CircleVertexBufferPtr->Thickness = circleRenderer.thickness;
			s_Data.CircleVertexBufferPtr->Fade = circleRenderer.fade;
			s_Data.CircleVertexBufferPtr++;
		}
		s_Data.CircleIndexCount += 6;
		RenderStat.TriangleCount += 2;
		drawnTriangles += 2;
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
		RenderStat.TriangleCount += 2;
		drawnTriangles += 2;
	}

	void Renderer::startBatch() {
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.CircleIndexCount = 0;
		s_Data.CircleVertexBufferPtr = s_Data.CircleVertexBufferBase;

		drawnTriangles = 0;
	}
	void Renderer::nextBatch() {
		submit();
		startBatch();
	}

	void Renderer::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount) {
		vertexArray->bind();
		uint32_t count = indexCount ? indexCount : vertexArray->getIndexBuffer()->getCount();
		GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
	}
}


