#include "Scene.h"

namespace Simulator {

	void Scene::render() const{
		for (const auto* obj: v_sceneGameObjects) {
			obj->render();
		}
	}
	void Scene::addGameObject(GameObject* obj){
		v_sceneGameObjects.push_back(obj);
	}

}