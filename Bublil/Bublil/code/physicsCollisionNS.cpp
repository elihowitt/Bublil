#include"physicsCollisionNS.h"

#pragma once

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
				centre = centre_;
				radius = radius_;
				break;
			case phy::col::CBT_BOX:
				break;
			case phy::col::CBT_SKELETON:
				break;
			default:
				break;
			}
		}

		CollisionBody::CollisionBody(const CollisionBody & other)
		{
			CBT_type = other.CBT_type;

			switch (CBT_type)
			{
			case phy::col::CBT_POINT:
				centre = new glm::vec3(*other.centre);
				break;

			case phy::col::CBT_RAY:
			case phy::col::CBT_RAY_SEGMENT:
				centre = new glm::vec3(*other.centre);
				positions = new glm::vec3(*other.positions);
				break;

			case phy::col::CBT_PLANE:
				positions = new glm::vec3[3];
				positions[0] = other.positions[0];
				positions[1] = other.positions[1];
				positions[2] = other.positions[2];
				break;

			case phy::col::CBT_CIRCLE:
				positions = new glm::vec3[3];
				positions[0] = other.positions[0];
				positions[1] = other.positions[1];
				positions[2] = other.positions[2];

				radius = new float(*other.radius);
				break;

			case phy::col::CBT_TRIANGLE:
				positions = new glm::vec3[3];
				positions[0] = other.positions[0];
				positions[1] = other.positions[1];
				positions[2] = other.positions[2];
				break;

			case phy::col::CBT_RECTANGLE:
				positions = new glm::vec3[4];
				positions[0] = other.positions[0];
				positions[1] = other.positions[1];
				positions[2] = other.positions[2];
				positions[3] = other.positions[3];
				break;

			case phy::col::CBT_SPHERE:
				centre = new glm::vec3(*other.centre);
				
				radius = new float(*other.radius);
				break;

			case phy::col::CBT_BOX:
				positions = new glm::vec3[8];
				for (int i = 0; i < 8; ++i)
					positions[i] = other.positions[i];
				break;

			case phy::col::CBT_SKELETON:
				positionsSize = new int(*other.positionsSize);
				positions = new glm::vec3[*positionsSize];
				for (int i = 0; i < *positionsSize; ++i)
					positions[i] = other.positions[i];

				indiciesSize = new int(*other.indiciesSize);
				indicies = new glm::vec3[*indiciesSize];
				for (int i = 0; i < *indiciesSize; ++i)
					indicies[i] = other.indicies[i];
				break;
			default:
				break;
			}
		}

		CollisionBody::~CollisionBody()
		{
			switch (CBT_type)
			{
			case phy::col::CBT_POINT:
				if (centre != nullptr)
					delete centre;
				break;
			case phy::col::CBT_RAY:
			case phy::col::CBT_RAY_SEGMENT:
				if (centre != nullptr)
					delete centre;
				if (positions != nullptr)
					delete positions;
				break;
			case phy::col::CBT_PLANE:
				if (positions != nullptr)
					delete[] positions;
				break;
			case phy::col::CBT_CIRCLE:
				if (positions != nullptr)
					delete[] positions;
				if (radius != nullptr)
					delete radius;
				break;
			case phy::col::CBT_TRIANGLE:
				if (positions != nullptr)
					delete[] positions;
				break;
			case phy::col::CBT_RECTANGLE:
				if (positions != nullptr)
					delete[] positions;
				break;
			case phy::col::CBT_SPHERE:
				if (centre != nullptr)
					delete centre;
				if (radius != nullptr)
					delete radius;
				break;
			case phy::col::CBT_BOX:
				if (positions != nullptr)
					delete[] positions;
				break;
			case phy::col::CBT_SKELETON:
				if (positions != nullptr)
					delete[] positions;
				if (positionsSize != nullptr)
					delete positionsSize;

				if (indicies != nullptr)
					delete[] indicies;
				if (indiciesSize != nullptr)
					delete indiciesSize;
				break;
			default:
				break;
			}
		}

		CollisionBody & CollisionBody::operator=(const CollisionBody & rhs)
		{
			CBT_type = rhs.CBT_type;

			switch (CBT_type)
			{
			case phy::col::CBT_POINT:
				centre = new glm::vec3(*rhs.centre);
				break;

			case phy::col::CBT_RAY:
			case phy::col::CBT_RAY_SEGMENT:
				centre = new glm::vec3(*rhs.centre);
				positions = new glm::vec3(*rhs.positions);
				break;

			case phy::col::CBT_PLANE:
				positions = new glm::vec3[3];
				positions[0] = rhs.positions[0];
				positions[1] = rhs.positions[1];
				positions[2] = rhs.positions[2];
				break;

			case phy::col::CBT_CIRCLE:
				positions = new glm::vec3[3];
				positions[0] = rhs.positions[0];
				positions[1] = rhs.positions[1];
				positions[2] = rhs.positions[2];

				radius = new float(*rhs.radius);
				break;

			case phy::col::CBT_TRIANGLE:
				positions = new glm::vec3[3];
				positions[0] = rhs.positions[0];
				positions[1] = rhs.positions[1];
				positions[2] = rhs.positions[2];
				break;

			case phy::col::CBT_RECTANGLE:
				positions = new glm::vec3[4];
				positions[0] = rhs.positions[0];
				positions[1] = rhs.positions[1];
				positions[2] = rhs.positions[2];
				positions[3] = rhs.positions[3];
				break;

			case phy::col::CBT_SPHERE:
				centre = new glm::vec3(*rhs.centre);

				radius = new float(*rhs.radius);
				break;

			case phy::col::CBT_BOX:
				positions = new glm::vec3[8];
				for (int i = 0; i < 8; ++i)
					positions[i] = rhs.positions[i];
				break;

			case phy::col::CBT_SKELETON:
				positionsSize = new int(*rhs.positionsSize);
				positions = new glm::vec3[*positionsSize];
				for (int i = 0; i < *positionsSize; ++i)
					positions[i] = rhs.positions[i];

				indiciesSize = new int(*rhs.indiciesSize);
				indicies = new glm::vec3[*indiciesSize];
				for (int i = 0; i < *indiciesSize; ++i)
					indicies[i] = rhs.indicies[i];
				break;
			default:
				break;
			}

			return *this;
		}

		CollisionBody CollisionBody::getSphere()const
		{
			if (CBT_type == CBT_SPHERE)
				return *this;
			if (radius != nullptr && centre != nullptr)
				return CollisionBody(CBT_SPHERE, isStatic, centre, radius, nullptr, nullptr, nullptr, nullptr);

			float *disSquared = new float(0);

			switch (CBT_type)
			{
			case phy::col::CBT_POINT:
				return CollisionBody(CBT_SPHERE, isStatic, centre, new float(0), nullptr, nullptr, nullptr, nullptr);
				break;
			case phy::col::CBT_RAY:
				*disSquared = distanceSquared(*centre, *positions);
				return CollisionBody(CBT_SPHERE, isStatic, centre, new float (sqrt(*disSquared)), nullptr, nullptr, nullptr, nullptr);
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
				return CollisionBody(CBT_SPHERE, isStatic, &VECTOR_ZERO, new float(sqrt(*disSquared)), nullptr, nullptr, nullptr, nullptr);
			case phy::col::CBT_SPHERE:
				break;
			default:
				break;
			}
		}
	}
}