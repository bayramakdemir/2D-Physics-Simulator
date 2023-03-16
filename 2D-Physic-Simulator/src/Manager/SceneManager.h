#pragma once
#include "../Object/Scene.h"

namespace Simulator {
	class SceneManager {
	public:
		void setActiveScene(Scene* scene) { currentScene = scene; };
		Scene* getActiveScene() const { return currentScene; };
		void renderScene(const int sceneId = 0) const;
	private:
		Scene* currentScene;
	};
}


