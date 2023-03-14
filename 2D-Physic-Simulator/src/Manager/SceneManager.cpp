#include "SceneManager.h"

namespace Simulator {
	void SceneManager::renderScene(const int sceneId) {
		getActiveScene()->render();
	}
}

