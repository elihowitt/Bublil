#pragma once

#include<glm\glm.hpp>

#include"CoreUtils.h"

namespace phy
{
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
}