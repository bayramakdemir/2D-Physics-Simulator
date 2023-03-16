#pragma once
#include "../Object/Object.h"

namespace Simulator {
	class Circle : public Object {
	public:
		Circle() :m_radius{ 1.0f } {};
		Circle(float radius) :m_radius{ radius } {};

		void render() const override;
		void setRadius(float r);
		float getRadius() const;
	private:
		float m_radius;
	};
}


