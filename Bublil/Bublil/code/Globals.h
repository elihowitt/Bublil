#include"glm/glm.hpp"

#include<vector>

#pragma once

enum STATE_FLAGS
{
	STATE_QUITE = -1,
	STATE_REPEAT = -2
};

enum MESHLIST
{
	//Must start at 0.
	MESH_TREE,



	//Must be last
	NUM_MESHES
};

enum TEXTURELIST
{
	//Must start at 0.
	TEXTURE_TREE,



	//Must be last
	NUM_TEXTURES
};

enum SHADERLIST
{
	//Must start at 0.
	GENERAL_SHADER,
	GUI_SHADER,


	//Must be last
	NUM_SHADERES
};

struct RenderPack
{
	MESHLIST mesh_id;
	TEXTURELIST texture_id;
	SHADERLIST shader_id;
};


