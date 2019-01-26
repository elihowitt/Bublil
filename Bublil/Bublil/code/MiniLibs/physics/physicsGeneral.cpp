#include"physics.h"

/*static*/ float phy::distanceSquared(const glm::vec3& a, const glm::vec3& b)
{
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z);
}

/*static*/ float phy::distance(const glm::vec3& a, const glm::vec3& b)
{
	return sqrt(distanceSquared(a, b));
}

phy::col::Collision phy::col::checks::sphere_sphere(const PhysicalEntity& a, const PhysicalEntity& b)
{
	//Temporary dumb code.
	Collision col;
	col.didHit = distance(*a.unit.position, *b.unit.position) <= (*a.body.radius + *b.body.radius);
	return col;
}

bool phy::col::doCollideSimple(const PhysicalEntity& a, const PhysicalEntity& b)
//Temporary dumb code.
{
	CollisionBody sa = a.body.getSphere(), sb = b.body.getSphere();
	Collision coll = checks::sphere_sphere(PhysicalEntity(a.unit, sa), PhysicalEntity(b.unit, sb));
	//Collision coll = checks::sphere_sphere(a, b);
	return coll.didHit;
}

bool phy::col::doCollideSimple(const CollisionBody & a_, const CollisionBody & b_)
{
	PhysicalEntity a(PhysicalUnit(), a_);
	PhysicalEntity b(PhysicalUnit(), b_);
	return doCollideSimple(a, b);
}
