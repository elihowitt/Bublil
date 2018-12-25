#include"glm/glm.hpp"

static glm::vec3 VECTOR_ZERO(0, 0, 0);

static float distanceSquared(const glm::vec3& a, const glm::vec3& b)
{
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z);
}
static float distance(const glm::vec3& a, const glm::vec3& b)
{
	return sqrt(distanceSquared(a, b));
}
