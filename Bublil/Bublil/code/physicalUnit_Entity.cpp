#include "physicsUnit_EntityNS.h"

//namespace phy
//{
	phy::PhysicalUnit::PhysicalUnit() :
		totalForce(0, 0, 0), mass(10),
		acceleration(0, 0, 0), velocity(0, 0, 0), position(0, 0, 0)
	{}
	phy::PhysicalUnit::PhysicalUnit(const glm::vec3 & pos, const glm::vec3 & vel, const glm::vec3 & acc, float mass_) :
		totalForce(0, 0, 0), mass(mass_),
		acceleration(acc), velocity(vel), position(pos)
	{}
	phy::PhysicalUnit::PhysicalUnit(const PhysicalUnit & other)
	{
		*this = other;//?
	}
	void phy::PhysicalUnit::applyForce(PhysicalUnit & entity, const glm::vec3 & force)
	{
		entity.totalForce += force;
	}

	void phy::PhysicalUnit::updatePosition(PhysicalUnit & entity, const float& dt)
	{
		entity.acceleration = entity.totalForce / entity.mass; //[sum(f) = m*a].
		entity.velocity += entity.acceleration*dt;
		entity.position += entity.velocity*dt;

		entity.totalForce = glm::vec3(0, 0, 0);//Everything was just applied.
	}
//}