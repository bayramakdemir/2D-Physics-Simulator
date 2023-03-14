#pragma once
#include "../Object/Scene.h"

namespace Simulator {
	class SceneManager {
	public:
		void setActiveScene(Scene* scene) { currentScene = scene; };
		Scene* getActiveScene() { return currentScene; };
		void renderScene(const int sceneId = 0);
	private:
		Scene* currentScene;
	};
}


