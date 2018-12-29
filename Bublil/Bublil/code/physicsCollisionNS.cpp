#include"physicsNS.h"

namespace phy
{
	namespace col
	{
		CollisionBody::CollisionBody(const COLLISIONBODYTYPE& type_, const bool isStatic_,
			glm::vec3* centre_, float* radius_, glm::vec3* positions_, int* posSize, glm::vec3* indicies_, int* indSize)
			: CBT_type(type_), isStatic(isStatic_)
		{
			switch (CBT_type)
			{
			case phy::col::CBT_POINT:
				break;
			case phy::col::CBT_RAY:
				break;
			case phy::col::CBT_RAY_SEGMENT:
				break;
			case phy::col::CBT_PLANE:
				break;
			case phy::col::CBT_CIRCLE:
				break;
			case phy::col::CBT_TRIANGLE:
				break;
			case phy::col::CBT_RECTANGLE:
				break;
			case phy::col::CBT_SPHERE:
				break;
			case phy::col::CBT_BOX:
				break;
			case phy::col::CBT_SKELETON:
				break;
			default:
				break;
			}
		}

		CollisionBody CollisionBody::getSphere()const
		{
			if (CBT_type == CBT_SPHERE)
				return *this;
			if (radius != nullptr && centre != nullptr)
				return CollisionBody(CBT_SPHERE, isStatic, centre, radius, nullptr, nullptr, nullptr, nullptr);

			float *disSquared = new float;
			*disSquared = 0;

			switch (CBT_type)
			{
			case phy::col::CBT_POINT:
				break;
			case phy::col::CBT_RAY:
				break;
			case phy::col::CBT_RAY_SEGMENT:
				break;
			case phy::col::CBT_PLANE:
				break;
			case phy::col::CBT_CIRCLE:
				break;
			case phy::col::CBT_TRIANGLE:
				break;
			case phy::col::CBT_RECTANGLE:
				break;

			case phy::col::CBT_BOX:
				break;
			case phy::col::CBT_SKELETON:
				for (int i = 0; i < *positionsSize; ++i)
				{
					float curr = distanceSquared(positions[i], glm::vec3(0,0,0));
					if (curr > *disSquared)
						*disSquared = curr;
				}
				return CollisionBody(CBT_SPHERE, isStatic, &VECTOR_ZERO, disSquared, nullptr, nullptr, nullptr, nullptr);
			case phy::col::CBT_SPHERE:
				break;
			default:
				break;
			}
		}



		Collision doCollide(const CollisionBody& a, const CollisionBody& b)
		{
			switch (a.CBT_type)
			{
			case phy::col::CBT_POINT:
				switch (b.CBT_type)
				{
				case phy::col::CBT_POINT:
					break;
				case phy::col::CBT_RAY:
					break;
				case phy::col::CBT_RAY_SEGMENT:
					break;
				case phy::col::CBT_PLANE:
					break;
				case phy::col::CBT_CIRCLE:
					break;
				case phy::col::CBT_TRIANGLE:
					break;
				case phy::col::CBT_RECTANGLE:
					break;
				case phy::col::CBT_SPHERE:
					break;
				case phy::col::CBT_BOX:
					break;
				case phy::col::CBT_SKELETON:
					break;
				default:
					break;
				}
				break;
			case phy::col::CBT_RAY:
				switch (b.CBT_type)
				{
				case phy::col::CBT_POINT:
					break;
				case phy::col::CBT_RAY:
					break;
				case phy::col::CBT_RAY_SEGMENT:
					break;
				case phy::col::CBT_PLANE:
					break;
				case phy::col::CBT_CIRCLE:
					break;
				case phy::col::CBT_TRIANGLE:
					break;
				case phy::col::CBT_RECTANGLE:
					break;
				case phy::col::CBT_SPHERE:
					break;
				case phy::col::CBT_BOX:
					break;
				case phy::col::CBT_SKELETON:
					break;
				default:
					break;
				}
				break;
			case phy::col::CBT_RAY_SEGMENT:
				switch (b.CBT_type)
				{
				case phy::col::CBT_POINT:
					break;
				case phy::col::CBT_RAY:
					break;
				case phy::col::CBT_RAY_SEGMENT:
					break;
				case phy::col::CBT_PLANE:
					break;
				case phy::col::CBT_CIRCLE:
					break;
				case phy::col::CBT_TRIANGLE:
					break;
				case phy::col::CBT_RECTANGLE:
					break;
				case phy::col::CBT_SPHERE:
					break;
				case phy::col::CBT_BOX:
					break;
				case phy::col::CBT_SKELETON:
					break;
				default:
					break;
				}
				break;
			case phy::col::CBT_PLANE:
				switch (b.CBT_type)
				{
				case phy::col::CBT_POINT:
					break;
				case phy::col::CBT_RAY:
					break;
				case phy::col::CBT_RAY_SEGMENT:
					break;
				case phy::col::CBT_PLANE:
					break;
				case phy::col::CBT_CIRCLE:
					break;
				case phy::col::CBT_TRIANGLE:
					break;
				case phy::col::CBT_RECTANGLE:
					break;
				case phy::col::CBT_SPHERE:
					break;
				case phy::col::CBT_BOX:
					break;
				case phy::col::CBT_SKELETON:
					break;
				default:
					break;
				}
				break;
			case phy::col::CBT_CIRCLE:
				switch (b.CBT_type)
				{
				case phy::col::CBT_POINT:
					break;
				case phy::col::CBT_RAY:
					break;
				case phy::col::CBT_RAY_SEGMENT:
					break;
				case phy::col::CBT_PLANE:
					break;
				case phy::col::CBT_CIRCLE:
					break;
				case phy::col::CBT_TRIANGLE:
					break;
				case phy::col::CBT_RECTANGLE:
					break;
				case phy::col::CBT_SPHERE:
					break;
				case phy::col::CBT_BOX:
					break;
				case phy::col::CBT_SKELETON:
					break;
				default:
					break;
				}
				break;
			case phy::col::CBT_TRIANGLE:
				switch (b.CBT_type)
				{
				case phy::col::CBT_POINT:
					break;
				case phy::col::CBT_RAY:
					break;
				case phy::col::CBT_RAY_SEGMENT:
					break;
				case phy::col::CBT_PLANE:
					break;
				case phy::col::CBT_CIRCLE:
					break;
				case phy::col::CBT_TRIANGLE:
					break;
				case phy::col::CBT_RECTANGLE:
					break;
				case phy::col::CBT_SPHERE:
					break;
				case phy::col::CBT_BOX:
					break;
				case phy::col::CBT_SKELETON:
					break;
				default:
					break;
				}
				break;
			case phy::col::CBT_RECTANGLE:
				switch (b.CBT_type)
				{
				case phy::col::CBT_POINT:
					break;
				case phy::col::CBT_RAY:
					break;
				case phy::col::CBT_RAY_SEGMENT:
					break;
				case phy::col::CBT_PLANE:
					break;
				case phy::col::CBT_CIRCLE:
					break;
				case phy::col::CBT_TRIANGLE:
					break;
				case phy::col::CBT_RECTANGLE:
					break;
				case phy::col::CBT_SPHERE:
					break;
				case phy::col::CBT_BOX:
					break;
				case phy::col::CBT_SKELETON:
					break;
				default:
					break;
				}
				break;
			case phy::col::CBT_SPHERE:
				switch (b.CBT_type)
				{
				case phy::col::CBT_POINT:
					break;
				case phy::col::CBT_RAY:
					break;
				case phy::col::CBT_RAY_SEGMENT:
					break;
				case phy::col::CBT_PLANE:
					break;
				case phy::col::CBT_CIRCLE:
					break;
				case phy::col::CBT_TRIANGLE:
					break;
				case phy::col::CBT_RECTANGLE:
					break;
				case phy::col::CBT_SPHERE:
					return checks::sphere_sphere(a, b);
					break;
				case phy::col::CBT_BOX:
					break;
				case phy::col::CBT_SKELETON:
					break;
				default:
					break;
				}
				break;
			case phy::col::CBT_BOX:
				switch (b.CBT_type)
				{
				case phy::col::CBT_POINT:
					break;
				case phy::col::CBT_RAY:
					break;
				case phy::col::CBT_RAY_SEGMENT:
					break;
				case phy::col::CBT_PLANE:
					break;
				case phy::col::CBT_CIRCLE:
					break;
				case phy::col::CBT_TRIANGLE:
					break;
				case phy::col::CBT_RECTANGLE:
					break;
				case phy::col::CBT_SPHERE:
					break;
				case phy::col::CBT_BOX:
					break;
				case phy::col::CBT_SKELETON:
					break;
				default:
					break;
				}
				break;
			case phy::col::CBT_SKELETON:
				switch (b.CBT_type)
				{
				case phy::col::CBT_POINT:
					break;
				case phy::col::CBT_RAY:
					break;
				case phy::col::CBT_RAY_SEGMENT:
					break;
				case phy::col::CBT_PLANE:
					break;
				case phy::col::CBT_CIRCLE:
					break;
				case phy::col::CBT_TRIANGLE:
					break;
				case phy::col::CBT_RECTANGLE:
					break;
				case phy::col::CBT_SPHERE:
					break;
				case phy::col::CBT_BOX:
					break;
				case phy::col::CBT_SKELETON:
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}

		bool doCollideSimple(const CollisionBody& a, const CollisionBody& b)
			//Temporary dumb code.
		{
			//CollisionBody sa = a.getSphere(), sb = b.getSphere();
			//Collision coll = checks::sphere_sphere(sa, sb);
			Collision coll = checks::sphere_sphere(a, b);
			return coll.didHit;
		}
		namespace checks
		{
			Collision sphere_sphere(const CollisionBody& a, const CollisionBody& b)
			{
				//Temporary dumb code.
				Collision col;
				col.didHit = distance(*a.centre, *b.centre) <= (*a.radius + *b.radius);
				return col;
			}
		}
	}
}