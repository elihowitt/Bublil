#pragma once

#include<glm\glm.hpp>

#include<vector>

namespace phy
{
	/*static*/ float distanceSquared(const glm::vec3& a, const glm::vec3& b);
	/*static*/ float distance(const glm::vec3& a, const glm::vec3& b);

	namespace col
	{
		enum CBT { CBT_RAY = 1, CBT_AABB = 2, CBT_SKEL = 3 };

		class CollisionBody
		{
		public:
			CollisionBody(const CBT& type_);
			CBT type;
		};

		class CollisionBodyAABB : public CollisionBody
		{
		public:
			CollisionBodyAABB(const glm::vec3 max_, const glm::vec3& min_);
			CollisionBodyAABB();
			glm::vec3 max;
			glm::vec3 min;
		};

		class CollisionBodySkel :public CollisionBodyAABB
		{
		public:
			CollisionBodySkel(const std::vector<glm::vec3> skelPositions_, const std::vector<glm::vec3> skelIndicies_);
			
			std::vector<glm::vec3> skelPositions;
			std::vector<glm::vec3> skelIndicies;
		};

		class CollisionBodyRay: public CollisionBody
		{
		public:
			CollisionBodyRay(const glm::vec3& start_, const glm::vec3& direction_, const glm::vec3& distance_);
			glm::vec3 start;
			glm::vec3 direction;
			glm::vec3 distance;
		};

		class Collision
		{
		public:
			Collision() {}
			Collision(const bool& didHit_, const glm::vec3& hitPoint_) :
				didHit(didHit_), hitPoint(hitPoint_) {}
			~Collision() {}

			//  If a collision actually occurred.
			bool didHit;

			//  The point of collision.
			glm::vec3 hitPoint; 

			explicit operator bool() const { return didHit; }
		};

	}

	class PhysicalUnit
	{
	public:
		PhysicalUnit();
		PhysicalUnit(const glm::vec3& pos, const glm::vec3& vel, const glm::vec3& acc, float mass_);
		PhysicalUnit(glm::vec3* pos, const glm::vec3& vel, const glm::vec3& acc, float mass_);

		PhysicalUnit(const PhysicalUnit& other);
		~PhysicalUnit() {}

		glm::vec3 totalForce;//Stores total forces applied to unit brfore update.

							 //Kinematic properties:
		glm::vec3 *position; //**Pointer for shared use with other classes.
		glm::vec3 velocity;
		glm::vec3 acceleration;
		float mass;

		//Adds a force to the total.
		static void applyForce(PhysicalUnit& entity, const glm::vec3& force);
		/*Takes the total forces and propagates down all
		*	the kinematic variables updating lastly the position. */
		static void updatePosition(PhysicalUnit& entity, const float& dt);
	};

	class PhysicalEntity
	{
	public:
		PhysicalEntity(const PhysicalUnit& unit_, col::CollisionBody* body_) :
			unit(unit_), body(body_) {}
		PhysicalEntity(const PhysicalUnit& unit_, const col::CollisionBody& body_) :
			unit(unit_) 
		{
			body = new col::CollisionBody(body_);
		}
		//PhysicalEntity(const PhysicalUnit& unit, const col::CollisionBody& collisionBody) {}
		//PhysicalEntity(const PhysicalEntity& other) {}

		~PhysicalEntity() {}

		PhysicalUnit unit;
		col::CollisionBody *body;
	};

	namespace col
	{
		bool testEntities	(const PhysicalEntity& a, const PhysicalEntity& b);
		bool testAABBs		(const PhysicalEntity& a, const PhysicalEntity& b);
		bool testSkels		(const PhysicalEntity& a, const PhysicalEntity& b);

		Collision doCollide		(const CollisionBodyRay& a, const PhysicalEntity& b);
		bool doCollideAABB		(const CollisionBodyRay& a, const PhysicalEntity& b);
		Collision doCollideSkel	(const CollisionBodyRay& a, const PhysicalEntity& b);
	}
	namespace literals
	{    
		float operator""nano(long double t);

		float operator""micro(long double t);

		float operator""milli(long double t);

		float operator""kilo(long double t);

		float operator""mega(long double t);

		float operator""giga(long double t);
	}
}
