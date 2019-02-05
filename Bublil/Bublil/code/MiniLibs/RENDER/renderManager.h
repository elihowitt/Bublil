#pragma once

#include"RENDER/core/mesh.h"
#include"RENDER/core/texture.h"
#include"RENDER/core/shader.h"

#include"../code/Globals.h"

namespace render
{

	class RenderManager
	{
	public:
		RenderManager(const std::string meshFiles[MESHLIST::NUM_MESHES], const std::string textureFiles[TEXTURELIST::NUM_TEXTURES], const std::string shaderFiles[SHADERLIST::NUM_SHADERES]);
		~RenderManager();
	private:
		Mesh* arr_meshs[MESHLIST::NUM_MESHES];
		Texture* arr_textures[TEXTURELIST::NUM_TEXTURES];
		Shader* arr_shaders[SHADERLIST::NUM_SHADERES];

		RenderPack boundPack;

		void tryBind(const RenderPack& pack);

		//template<class T, class... ARGS>
		//void updateShader(const SHADERLIST& id, ARGS... args)
		//{
		//	(T*)arr_shaders[id]->Update(args);
		//}
	public:
		//template<class T, class... ARGS>
		void render(const RenderPack& pack/*, ARGS... args*/)
		{
			tryBind(pack);
			//updateShader<T, ARGS>(pack.shader_id, shaderType, args);
			arr_meshs[pack.mesh_id]->Draw();
		}
	};
}
