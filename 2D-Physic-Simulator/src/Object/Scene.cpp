#include "Scene.h"

namespace Simulator {

	void Scene::render() const{
		for (const auto* obj: v_sceneObjects) {
			obj->render();
		}
	}
	void Scene::addObject(Object* obj){
		v_sceneObjects.push_back(obj);
	}

}