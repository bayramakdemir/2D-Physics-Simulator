#pragma once
#include "../Object/Object.h"
#include <vector>

namespace Simulator {
	class SceneManager;

	class Scene {
		friend class SceneManager;
	public:
		void addObject(Object* object);

	private:
		std::vector<Object*> v_sceneObjects;

		void render();
	};
}



