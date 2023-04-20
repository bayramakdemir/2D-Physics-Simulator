#pragma once
#include "Entity.h"
#include "OrthographicCamera.h"

namespace Simulator {

	class Scene {
	public:

		void render(const OrthographicCamera& camera) const;
		void update() const;
		void start() const;

		void removeEntity(Entity& e);
		Entity createEntity();

		//TODO: remove in future
		entt::registry* getRegistery(){
			return &m_registery;
		}
	private:
		entt::registry m_registery;
		friend class Entity;
	};
}



