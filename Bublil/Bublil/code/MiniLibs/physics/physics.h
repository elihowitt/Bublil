#pragma once

#include<glm\glm.hpp>

namespace phy
{
	/*static*/ float distanceSquared(const glm::vec3& a, const glm::vec3& b);
	/*static*/ float distance(const glm::vec3& a, const glm::vec3& b);

	namespace col
	{
		enum COLLISIONBODYTYPE
		{
			//A '-' means I hav yet to implement everything to-do with this body type.

			/*-*/CBT_POINT = 1,	     //Zero dimensional, one position.
									 /*
									 'centre'
									 */
			/*-*/CBT_RAY,		     //One dimensional, two positions.
									 /*
									 'centre'
									 'positions'
									 */
			/*-*/CBT_RAY_SEGMENT,    //One dimensional, two positions.
									 /*
									 'centre'
									 'positions'
									 */
			/*-*/CBT_PLANE,		     //Two dimensional, three positions.
									 /*
									 'positions'
									 */
			/*-*/CBT_CIRCLE,	     //Two dimensional, one position & two other positions to form the plane & a radius.
									 /*
									 'positions'
									 'radius'
									 */
			/*-*/CBT_TRIANGLE,	     //Two dimensional, three positions.
									 /*
									 'positions'
									 */
			/*-*/CBT_RECTANGLE,	     //Two dimensional, four positions.
									 /*
									 'positions'
									 */
			/*-*/CBT_SPHERE,	     //Three dimensional, one position & one radius.
									 /*
									 'centre'
									 'radius'
									 */
			/*-*/CBT_BOX,		     //Three dimensional, eight positions.
									 /*
									 'positions'
									 */
			/*-*/CBT_SKELETON	     //Three dimensional, an array of positions & array of indicies building triangles.
									 /*
									 'positions'
									 'positionsSize'
									 'indicies'
									 'indiciesSize'
									 */
		};


		class CollisionBody
		{
		public:
			CollisionBody(const COLLISIONBODYTYPE& type_,
				const bool isStatic_,
				glm::vec3* centre_, float* radius_,
				glm::vec3* positions_, int* posSize,
				glm::vec3* indicies_, int* indSize);
			CollisionBody(const CollisionBody& other);
			~CollisionBody();

			CollisionBody& operator=(const CollisionBody& rhs);

			COLLISIONBODYTYPE CBT_type;	//Type of body.

			bool isStatic;	//Does the body stay allways in place (like a wall).

							/* The following will be initialized & used
							*	deppending on this body type.
							*  For example a 'BOX' will not need a radius
							*	so no need to initiate nor use said field.	*/
			glm::vec3* centre;
			float* radius;
			glm::vec3* positions;
			int *positionsSize;
			glm::vec3* indicies;
			int *indiciesSize;

			//	Returns the sphere version of this body for simple checks.
			//	After calling once the variables will be stored fo later checks.
			CollisionBody getSphere()const;
		};

		class Collision
		{
		public:
			Collision() {}
			~Collision() {}

			bool didHit;		//  If a collision actually occurred.

								/* Pointers to the bodys hit.
								*  Used for applying the affects of the hit
								*  on thes bodys.                            */
			CollisionBody *body1, *body2;

			glm::vec3 hitPoint; //  The point of collision.
			glm::vec3 distance;	//	For projectile collisions like shooting. 
								//	Stores distance from 'shooter' to 'target'.

			explicit operator bool() const { return didHit; }
		};

	}

	class PhysicalUnit
	{
	public:
		PhysicalUnit();
		PhysicalUnit(const glm::vec3& pos, const glm::vec3& vel, const glm::vec3& acc, float mass_);

		PhysicalUnit(const PhysicalUnit& other);
		~PhysicalUnit() {}

		glm::vec3 totalForce;//Stores total forces applied to unit brfore update.

							 //Kinematic properties:
		glm::vec3 position;
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
		PhysicalEntity(const PhysicalUnit& unit_, const col::CollisionBody& body_) :
			unit(unit_), body(body_) {}
		//PhysicalEntity(const PhysicalUnit& unit, const col::CollisionBody& collisionBody) {}
		//PhysicalEntity(const PhysicalEntity& other) {}

		~PhysicalEntity() {}

		PhysicalUnit unit;
		col::CollisionBody body;
	};

	namespace col
	{
		namespace checks
		{
			Collision sphere_sphere(const PhysicalEntity& a, const PhysicalEntity& b);
		}
		bool doCollideSimple(const PhysicalEntity& a, const PhysicalEntity& b);
		bool doCollideSimple(const CollisionBody& a, const CollisionBody& b);
	}
	namespace literals
	{
		template<typename T>
		float nano(T t)
		{
			return t / 1000000000;
		}
		template<typename T>
		float micro(T t)
		{
			return t / 1000000;
		}
		template<typename T>
		float milli(T t)
		{
			return t / 100;
		}
		template<typename T>
		T kilo(T t)
		{
			return t * 1000;
		}
		template<typename T>
		T mega(T t)
		{
			return t * 1000000;
		}
		template<typename T>
		T giga(T t)
		{
			return t * 1000000000;
		}
	}
}
