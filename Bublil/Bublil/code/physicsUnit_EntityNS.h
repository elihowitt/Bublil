#pragma once

#include"physicsNS.h"

namespace phy
{
	class PhysicalUnit
	{
	public:
		PhysicalUnit();
		PhysicalUnit(const glm::vec3& pos, const glm::vec3& vel, const glm::vec3& acc, float mass_) :
			totalForce(0, 0, 0), mass(mass_),
			acceleration(acc), velocity(vel), position(pos)
		{}

		//PhysicalUnit(const PhysicalUnit& other);
		~PhysicalUnit() {}

		glm::vec3 totalForce;//Stores total forces applied to unit brfore update.

							 //Kinematic properties:
		glm::vec3 position;
		glm::vec3 velocity;
		glm::vec3 acceleration;
		float mass;

		//Adds a force to the total.
		static void applyForce(PhysicalUnit& entity, const glm::vec3& force) {
			entity.totalForce += force;
		}
		/*Takes the total forces and propagates down all
		*	the kinematic variables updating lastly the position. */
		static void updatePosition(PhysicalUnit& entity, const float& dt) {
			entity.acceleration = entity.totalForce / entity.mass; //[sum(f) = m*a].
			entity.velocity += entity.acceleration*dt;
			entity.position += entity.velocity*dt;

			entity.totalForce = glm::vec3(0, 0, 0);//Everything was just applied.
		}
	};

	class PhysicalEntity
	{
	public:
		PhysicalEntity(const PhysicalUnit& unit_, const col::CollisionBody& body_) :
			unit(unit_), body(body_) {}
		//PhysicalEntity(const PhysicalUnit& unit, const col::CollisionBody& collisionBody) {}
		//PhysicalEntity(const PhysicalEntity& other) {}

		~PhysicalEntity() {}

		PhysicalUnit unit;
		col::CollisionBody body;
	};
}
