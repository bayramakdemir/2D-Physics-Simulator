#pragma once
#include "Object/TransformComponent.h"

class RectangleEntity {
public:
	RectangleEntity();
	~RectangleEntity();

private:
	Simulator::TransformComponent tranform;
};

