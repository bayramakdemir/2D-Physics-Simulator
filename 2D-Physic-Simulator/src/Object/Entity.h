#pragma once
#include "../Core.h"
#include "entt/entt.hpp"

namespace Simulator {
	class Scene;

	class Entity {
	public:
		Entity() = default;
		Entity(Scene* scene);
		Entity(Scene* scene, entt::entity entity);
		Entity(const Entity& other) = default;

		template <typename T, typename... Args>
		T& addComponent(Args&&... args) {
			ASSERT(!hasComponent<T>() && "Entity alread have component");
			T& component = m_scene->m_registery.emplace<T>(m_entity, std::forward<Args>(args)...);
			return component;
		}

		template <typename T>
		void removeComponent() {
			ASSERT(hasComponent<T>() && "Entity does not have component");
			m_scene->m_registery.remove<T>(m_entity);
		}

		template <typename T>
		T& getComponent() {
			ASSERT(hasComponent<T>() && "Entity does not have component");
			T& component = m_scene->m_registery.get<T>(m_entity);
			return component;
		}

		template<typename T>
		bool hasComponent() {
			return m_scene->m_registery.any_of<T>(m_entity);
		}

		operator entt::entity() {
			return m_entity;
		}

	private:
		entt::entity m_entity; 
		Scene* m_scene; //the scene reference for entity which belong to 

	};
}


