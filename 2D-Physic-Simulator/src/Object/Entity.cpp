#include "Entity.h"
#include "Scene.h"

namespace Simulator {
	Entity::Entity(Scene* scene)
		: m_scene(scene), m_entity(scene->m_registery.create()) {
	}

	Entity::Entity(Scene* scene, entt::entity entity)
		: m_scene(scene), m_entity(entity) {
	}
}