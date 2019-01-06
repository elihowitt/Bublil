#pragma once

#include"physicsCollisionNS.h"

namespace phy
{
	class PhysicalUnit
	{
	public:
		PhysicalUnit() :
			totalForce(0, 0, 0), mass(10),
			acceleration(0, 0, 0), velocity(0, 0, 0), position(0, 0, 0)
		{}
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
	namespace col {
		namespace checks//All functions for checkiong specific collisions.
		{
			col::Collision sphere_sphere(const PhysicalEntity& a, const PhysicalEntity& b)
			{
				//Temporary dumb code.
				col::Collision col;
				col.didHit = distance(a.unit.position, b.unit.position) <= (*a.body.radius + *b.body.radius);
				return col;
			}
		}
		bool doCollideSimple(const PhysicalEntity& a, const PhysicalEntity& b)
			//Temporary dumb code.
		{
			CollisionBody sa = a.body.getSphere(), sb = b.body.getSphere();
			Collision coll = checks::sphere_sphere(PhysicalEntity(a.unit, sa), PhysicalEntity(b.unit, sb));
			//Collision coll = checks::sphere_sphere(a, b);
			return coll.didHit;
		}
		bool doCollideSimple(const CollisionBody& a, const CollisionBody& b) { return doCollideSimple(PhysicalEntity(PhysicalUnit(), a), PhysicalEntity(PhysicalUnit(), b)); }
	}
}
