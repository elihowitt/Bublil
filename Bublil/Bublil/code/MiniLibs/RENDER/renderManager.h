#pragma once

#include"RENDER/core/mesh.h"
#include"RENDER/core/texture.h"
#include"RENDER/core/shader.h"

#include"../code/Globals.h"

#include"RENDER\core\shaders\generalShader.h"
#include"RENDER\core\shaders\guiShader.h"

namespace render
{

	class RenderManager
	{
	public:
		RenderManager(const std::string meshFiles[MESHLIST::NUM_MESHES], const std::string textureFiles[TEXTURELIST::NUM_TEXTURES], const std::string shaderFiles[SHADERLIST::NUM_SHADERES]);
		~RenderManager();
	private:
		static Shader* CreateCustomeShaderByType(const SHADERLIST& type, const std::string& filename);

		Mesh* arr_meshs[MESHLIST::NUM_MESHES];
		Texture* arr_textures[TEXTURELIST::NUM_TEXTURES];
		Shader* arr_shaders[SHADERLIST::NUM_SHADERES];

		RenderPack boundPack;

		void tryBind(const RenderPack& pack);

		void updateShader(const ShaderUpdatePack& pack, const SHADERLIST& type);

	public:
		void render(const RenderPack& bind, const ShaderUpdatePack& update);
	};
}
