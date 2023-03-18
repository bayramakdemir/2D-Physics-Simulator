#include "GameObject.h"
namespace Simulator {

	void GameObject::addComponent(std::unique_ptr<Component> comp) {
		m_components.push_back(std::move(comp));
	}
}