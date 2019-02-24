#pragma once

#include"RENDER/core/camera.h"
#include"RENDER/core/transform.h"
#include<vector>

namespace render
{
	enum MESHLIST
	{
		//Must start at 0.
		MESH_TREE,
		MESH_POKEBALL,


		//Must be last
		NUM_MESHES
	};

	enum TEXTURELIST
	{
		//Must start at 0.
		TEXTURE_TREE,
		TEXTURE_POKEBALL,

		//Must be last
		NUM_TEXTURES
	};

	enum SHADERLIST
	{
		//Must start at 0.
		GENERAL_SHADER,
		RELATIVEPOSITION_SHADER,


		//Must be last
		NUM_SHADERES
	};

	struct ShaderUpdatePack
	{
		std::vector<Transform> transforms;
		std::vector<glm::vec3> vectors;
		Camera* camera;

		void clearAll() { transforms.clear(); vectors.clear(); camera = nullptr; }
	};

	struct RenderPack
	{
		MESHLIST mesh_id;
		TEXTURELIST texture_id;
		SHADERLIST shader_id;
	};

	struct Drawable
	{
		RenderPack renderPack;
		ShaderUpdatePack updatePack;
	};
}


