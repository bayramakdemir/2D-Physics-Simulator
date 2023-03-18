#pragma once
#include "Transform.h"
#include <vector>
#include <memory>
#include "Component.h"
#include "Material.h"

namespace Simulator {
	class GameObject {
	public:
		Transform transform; //transform of gameobject

		virtual void render() const{};

		const Material& getMaterial() const { return m_material; }

		void addComponent(std::unique_ptr<Component> comp);
		virtual ~GameObject() {};
		GameObject() {};

	protected:
		
	private:
		std::vector<std::unique_ptr<Component>> m_components;
		Material m_material;
	};
}


