#pragma once
#include "../Object/Object.h"
#include <vector>
#include <memory>

namespace Simulator {
	class SceneManager;

	class Scene {
		friend class SceneManager;
	public:
		void addObject(Object* obj);

	private:
		std::vector<Object*> v_sceneObjects;

		void render() const;
	};
}



