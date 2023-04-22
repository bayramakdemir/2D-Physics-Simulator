#include "Solver.h"
#include "../Object/RendererComponent.h"

namespace Simulator {
	float Solver::s_gravity = -5000.0f;
	glm::vec2 Solver::s_constraint_center = {0.0f,0.0f};
	float Solver::s_constraint_radius = { 20.0f };

	void Solver::Solve(Scene& scene, float dt) {
		//TODO: substep;
		const int sub_step = 4;
		const float step_dt = dt / static_cast<float>(sub_step);
		for (int i{ sub_step }; i > 0; i--) {
			
			auto view = (*scene.getRegistery()).view<TransformComponent, CircleRigidbody>();
			for (auto [ent1,transform1, rb1] : view.each()) {
			
				//apply s_gravity
				rb1.accelerate({ 0.0f, s_gravity * step_dt });

				//check collisions
		
				for (auto ent2 : view) {
					if (ent1 != ent2) {
						TransformComponent& transform2 = view.get<TransformComponent>(ent2);
						SolveCollisions(transform1, transform2);
					}
				}
				//apply constraint
				ApplyConstraint(transform1);

				//update
				rb1.step(step_dt);
			}
		}
	}

	void Solver::ApplyConstraint(TransformComponent& transform) {
		const glm::vec2 dist = s_constraint_center - glm::vec2(transform.getPosition().x, transform.getPosition().y);
		
		float length = glm::length(dist);
		
		if (length > (s_constraint_radius - transform.getScale().x)) {
			const glm::vec2 n = dist / length;
			const glm::vec2 border = s_constraint_center - n * (s_constraint_radius - transform.getScale().x);
			transform.setPosition({ border,0.0f });
		}
	}


	void Solver::SolveCollisions(TransformComponent& entity, TransformComponent& other) {
		constexpr float responce_coeff = 0.9f;
		//if collide, find collision axes which means that
		// distance =  object2.pos - object1.pos
		// collision distance = object1.radius + object2.radius - distance
		//object1.pos -= collision distance * 0.5f
		//object2.pos += collision distance * 0.5f
		const glm::vec3 distance = other.getPosition() - entity.getPosition();
		const float collision_distance = entity.getScale().x*0.5f + other.getScale().x * 0.5f - glm::length(distance);

		if (collision_distance > 0) {
			const float ratio1 = entity.getScale().x / (entity.getScale().x + other.getScale().x);
			const float ratio2 = other.getScale().x / (entity.getScale().x + other.getScale().x);
			const float delta = 0.5f * responce_coeff * collision_distance;
			const glm::vec3 n_dist = glm::normalize(distance);
			other.setPosition(other.getPosition() + n_dist * ratio2 * delta);
			entity.setPosition(entity.getPosition() - n_dist * ratio1 * delta);
		}
	}
}