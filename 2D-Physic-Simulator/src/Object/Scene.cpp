#include "Scene.h"
#include "TransformComponent.h"
#include "RendererComponent.h"
#include "../Graphics/Renderer.h"


namespace Simulator {

	void Scene::render(const OrthographicCamera& camera) const {
		SimulatorCore::Renderer::BeginScene(camera);

		auto view = m_registery.view<TransformComponent, CircleRendererComponent>();
		for (auto entity : view) {
			auto [transform, circle] = view.get<TransformComponent, CircleRendererComponent>(entity);
			SimulatorCore::Renderer::DrawCircle(transform.getTransformationMatrix(), circle);
		}

		SimulatorCore::Renderer::EndScene();
	}
	void Scene::update() const {

	}
	void Scene::start() const {

	}

	void Scene::removeEntity(Entity& e) {
		m_registery.destroy(e);
	}
	Entity Scene::createEntity() {
		Entity e = { this };
		e.addComponent<TransformComponent>();
		return e;
	}
}