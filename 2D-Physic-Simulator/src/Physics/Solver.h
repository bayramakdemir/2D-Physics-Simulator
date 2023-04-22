#pragma once
#include "../Object/Scene.h"
#include "../Object/PhysicComponent.h"

namespace Simulator {
	class Solver {
	public:
		Solver() = delete;

		static void Solve(Scene& scene, float dt);
	
		static void ApplyConstraint(TransformComponent& transform);
	
		static void SolveCollisions(TransformComponent& entity, TransformComponent& other);

		static float s_gravity;
		static glm::vec2 s_constraint_center;
		static float s_constraint_radius;
	};
}