#include "Scene.h"
#include "TransformComponent.h"

namespace Simulator {

	void Scene::addEntity(){
		const auto entity = m_registery.create();

		m_registery.emplace<TransformComponent>(entity);
	}
}