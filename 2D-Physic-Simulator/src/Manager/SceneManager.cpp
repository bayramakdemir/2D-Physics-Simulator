#include "SceneManager.h"

namespace Simulator {
	void SceneManager::renderScene(const int sceneId) const{
		getActiveScene()->render();
	}
}

