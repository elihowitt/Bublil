#pragma once

#include<glm\glm.hpp>

namespace phy
{
	namespace col
	{
		enum COLLISIONBODYTYPE
		{
			CBT_POINT = 1,	//Zero dimensional, one position.
			CBT_RAY,		//One dimensional, two positions.
			CBT_RAY_SEGMENT,//One dimensional, two positions.
			CBT_PLANE,		//Two dimensional, three positions.
			CBT_CIRCLE,		//Two dimensional, one position & two other positions to form the plane & a radius.
			CBT_TRIANGLE,	//Two dimensional, three positions.
			CBT_RECTANGLE,	//Two dimensional, four positions.
			CBT_SPHERE,		//Three dimensional, one position & one radius.
			CBT_BOX,		//Three dimensional, eight positions.
			CBT_SKELETON	//Three dimensional, an array of positions & array of indicies building triangles.
		};
		class GeneralCollisionBody
		{
		public:
			GeneralCollisionBody(const COLLISIONBODYTYPE& type_,
				glm::vec3* centre_, float* radius_, glm::vec3* positions_, glm::vec3* indicies_);
			~GeneralCollisionBody();
			
			COLLISIONBODYTYPE type;

			glm::vec3* centre;
			float* radius;
			glm::vec3* positions;
			glm::vec3* indicies;
		};
	}

	class PhysicalUnit
	{
	public:
		PhysicalUnit();
		PhysicalUnit(const glm::vec3& pos, const glm::vec3& vel, const glm::vec3& acc, float mass_);
		PhysicalUnit(const PhysicalUnit& other);
		~PhysicalUnit();

		glm::vec3 position;
		glm::vec3 velocity;
		glm::vec3 acceleration;
		float mass;

		static void applyForce(PhysicalUnit& entity, const glm::vec3& force);
		static void updatePosition(PhysicalUnit& entity, const float& dt);
	};
	class PhysicalEntity
	{
	public:
		PhysicalEntity();
		PhysicalEntity(const PhysicalUnit& unit, const col::GeneralCollisionBody& collisionBody);
		PhysicalEntity(const PhysicalEntity& other);

		~PhysicalEntity();
		
		PhysicalUnit unit; 
		col::GeneralCollisionBody body;
	};
}
