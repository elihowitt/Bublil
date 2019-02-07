#pragma once

#include"camera.h"
#include"transform.h"
#include<vector>

class ShaderUpdatePack
{
public:
	ShaderUpdatePack() {}
	~ShaderUpdatePack() {}

	std::vector<Transform> transforms;
	std::vector<glm::vec3> vectors;
	Camera* camera;
};
