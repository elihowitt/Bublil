#pragma once

#include"physicsUnit_EntityNS.h"

namespace phy
{
	namespace col
	{
		//Returns true if there is a collibsion, if there is then third param will be set to collision point.body.
		Collision GetCollision(const PhysicalEntity& a, const PhysicalEntity& b)
		{


			switch (a.body.CBT_type)
			{
			case phy::col::CBT_POINT:
				switch (b.body.CBT_type)
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
				switch (b.body.CBT_type)
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
				switch (b.body.CBT_type)
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
				switch (b.body.CBT_type)
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
				switch (b.body.CBT_type)
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
				switch (b.body.CBT_type)
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
				switch (b.body.CBT_type)
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
				switch (b.body.CBT_type)
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
				switch (b.body.CBT_type)
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
				switch (b.body.CBT_type)
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
		

		//bool doCollideSimple(const PhysicalEntity& a, const PhysicalEntity& b)
		//	//Temporary dumb code.
		//{
		//	CollisionBody sa = a.body.getSphere(), sb = b.body.getSphere();
		//	Collision coll = checks::sphere_sphere(PhysicalEntity(a.unit, sa), PhysicalEntity(b.unit, sb));
		//	//Collision coll = checks::sphere_sphere(a, b);
		//	return coll.didHit;
		//}
		namespace checks
		{
			//Collision sphere_sphere(const PhysicalEntity& a, const PhysicalEntity& b)
			//{
			//	//Temporary dumb code.
			//	Collision col;
			//	col.didHit = distance(a.unit.position, b.unit.position) <= (*a.body.radius + *b.body.radius);
			//	return col;
			//}
		}
	}
}
