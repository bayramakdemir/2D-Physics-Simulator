#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "../Core.h"
#include "Texture2D.h"
#include "../Object/OrthographicCamera.h"
#include "../Object/TransformComponent.h"

namespace SimulatorCore {

	class Renderer {
	public:
		static void Init();
		static void Dispose();

		//begin scene and and scene is called once
		static void BeginScene(const Simulator::OrthographicCamera& camera);
		static void EndScene();

		static void DrawCircle(const glm::vec2& pos, const float radius);
		static void DrawQuad(Simulator::TransformComponent& transform);
		static void DrawQuad(const glm::vec3& pos);
		static void DrawQuad(const glm::mat4& transform);
	

	private:
		static void submit();
		static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0);
		static void startBatch();
	};



}

