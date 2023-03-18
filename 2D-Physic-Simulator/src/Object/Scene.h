#pragma once
#include "../Object/GameObject.h"
#include <vector>
#include <memory>

namespace Simulator {
	class SceneManager;

	class Scene {
		friend class SceneManager;
	public:
		void addGameObject(GameObject* obj);
		void render() const;

	private:
		std::vector<GameObject*> v_sceneGameObjects;

	};
}



