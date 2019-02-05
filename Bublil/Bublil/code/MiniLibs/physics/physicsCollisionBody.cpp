#include"PHYSICS\physics.h"

phy::col::CollisionBody::CollisionBody(const CBT& type_) :type(type_)
{}

phy::col::CollisionBodyAABB::CollisionBodyAABB(const glm::vec3 max_, const glm::vec3& min_) :
	CollisionBody(CBT_AABB), min(min_), max(max_) {}

phy::col::CollisionBodyAABB::CollisionBodyAABB():CollisionBody(CBT_AABB)
{}

phy::col::CollisionBodySkel::CollisionBodySkel(const std::vector<glm::vec3> skelPositions_, const std::vector<glm::vec3> skelIndicies_): skelIndicies(skelIndicies_)
{
	float extreams[6];
	//Least x, Most X, Least Y Most Y...
	for (int i = 0; i < skelPositions_.size(); ++i)
	{
		glm::vec3 p = skelPositions_[i];
		skelPositions.push_back(p);

		if (p.x < extreams[0])
			extreams[0] = p.x;
		else if (p.x > extreams[1])
			extreams[1] = p.x;

		if (p.y < extreams[2])
			extreams[2] = p.y;
		else if (p.y > extreams[3])
			extreams[3] = p.y;

		if (p.z < extreams[4])
			extreams[4] = p.z;
		else if (p.z > extreams[5])
			extreams[0] = p.x;
	}
	this->max = glm::vec3(extreams[0], extreams[2], extreams[4]);
	this->min = glm::vec3(extreams[1], extreams[3], extreams[5]);

	type = CBT_SKEL;
}

phy::col::CollisionBodyRay::CollisionBodyRay(const glm::vec3& start_, const glm::vec3& direction_, const glm::vec3& distance_) :
	CollisionBody(CBT_RAY), start(start_), direction(direction_), distance(distance_)
{}