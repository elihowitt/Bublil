#include"physics.h"

/*static*/ float phy::distanceSquared(const glm::vec3& a, const glm::vec3& b)
{
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z);
}

/*static*/ float phy::distance(const glm::vec3& a, const glm::vec3& b)
{
	return sqrt(distanceSquared(a, b));
}

float phy::literals::operator""nano(long double t)
{
	return t / 1000000000;
}

float phy::literals::operator""micro(long double t)
{
	return t / 1000000;
}

float phy::literals::operator""milli(long double t)
{
	return t / 1000;
}

float phy::literals::operator""kilo(long double t)
{
	return t * 1000;
}

float phy::literals::operator""mega(long double t)
{
	return t * 1000000;
}

float phy::literals::operator""giga(long double t)
{
	return t * 1000000000;
}

bool phy::col::testEntities(const PhysicalEntity& a, const PhysicalEntity& b)
{
	//If right hand is false i wont compute left-hand.
	return testAABBs(a, b) && testSkels(a, b);
}

bool phy::col::testAABBs(const PhysicalEntity& a, const PhysicalEntity& b)
{
	glm::vec3 pushA = *a.unit.position, pushB = *b.unit.position;

	return (
		pushA.x + ((CollisionBodyAABB*)a.body)->max.x >= pushB.x + ((CollisionBodyAABB*)b.body)->min.x &&
		pushA.x + ((CollisionBodyAABB*)a.body)->min.x <= pushB.x + ((CollisionBodyAABB*)b.body)->max.x &&
		pushA.y + ((CollisionBodyAABB*)a.body)->max.x >= pushB.y + ((CollisionBodyAABB*)b.body)->min.y &&
		pushA.y + ((CollisionBodyAABB*)a.body)->min.x >= pushB.y + ((CollisionBodyAABB*)b.body)->min.y &&
		pushA.z + ((CollisionBodyAABB*)a.body)->max.x >= pushB.z + ((CollisionBodyAABB*)b.body)->min.z &&
		pushA.z + ((CollisionBodyAABB*)a.body)->min.x >= pushB.z + ((CollisionBodyAABB*)b.body)->min.z
		);
}

bool phy::col::testSkels(const PhysicalEntity& a, const PhysicalEntity& b)
{
	//Right now, and for my purpose we dont really need this I hope.
	return true;
}

phy::col::Collision phy::col::doCollide(const CollisionBodyRay & a, const PhysicalEntity & b)
{
	if(doCollideAABB(a, b))
		return doCollideSkel(a, b);
	return Collision(false, glm::vec3());
}

bool phy::col::doCollideAABB(const CollisionBodyRay & a, const PhysicalEntity & b)
{
	return false;
}

phy::col::Collision phy::col::doCollideSkel(const CollisionBodyRay & a, const PhysicalEntity & b)
{
	return Collision();
}

