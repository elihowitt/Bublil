#include "renderManager.h"

render::RenderManager::RenderManager(const std::string meshFiles[MESHLIST::NUM_MESHES], const std::string textureFiles[TEXTURELIST::NUM_TEXTURES], const std::string shaderFiles[SHADERLIST::NUM_SHADERES])
{
	for (int i = 0; i < MESHLIST::NUM_MESHES; ++i)
		arr_meshs[i] = new Mesh(meshFiles[i]);

	for (int i = 0; i < TEXTURELIST::NUM_TEXTURES; ++i)
		arr_textures[i] = new Texture(meshFiles[i]);

	for (int i = 0; i < SHADERLIST::NUM_SHADERES; ++i)
		arr_shaders[i] = new Shader(meshFiles[i]);
}

render::RenderManager::~RenderManager()
{
	for (int i = 0; i < MESHLIST::NUM_MESHES; ++i)
		delete arr_meshs[i];

	for (int i = 0; i < TEXTURELIST::NUM_TEXTURES; ++i)
		delete arr_textures[i];

	for (int i = 0; i < SHADERLIST::NUM_SHADERES; ++i)
		delete arr_shaders[i];
}

void render::RenderManager::tryBind(const RenderPack & pack)
{
	if (boundPack.texture_id != pack.texture_id)
	{
		arr_textures[pack.texture_id]->Bind(0);
		boundPack.texture_id = pack.texture_id;
	}
	if (boundPack.shader_id != pack.shader_id)
	{
		arr_shaders[pack.shader_id]->Bind();
		boundPack.shader_id = pack.shader_id;
	}
}

