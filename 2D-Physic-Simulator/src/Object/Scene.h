#pragma once
#include <vector>
#include <memory>
#include "entt/entt.hpp"

namespace Simulator {
	class SceneManager;

	class Scene {
		friend class SceneManager;
	public:
		void addEntity();
		void render() const;

	private:
		entt::registry m_registery;
	};
}



