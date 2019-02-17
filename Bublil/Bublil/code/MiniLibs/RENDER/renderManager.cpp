#include "renderManager.h"

static render::SHADERLIST to_shaderType(const int& num)
{
	switch (num)
	{
	case render::SHADERLIST::GENERAL_SHADER:
		return render::SHADERLIST::GENERAL_SHADER;

	case render::SHADERLIST::NUM_SHADERES:
	default:
		return render::SHADERLIST::NUM_SHADERES;
	}
}

render::RenderManager::RenderManager(const std::string meshFiles[MESHLIST::NUM_MESHES], const std::string textureFiles[TEXTURELIST::NUM_TEXTURES], const std::string shaderFiles[SHADERLIST::NUM_SHADERES])
{
	for (int i = 0; i < MESHLIST::NUM_MESHES; ++i)
		arr_meshs[i] = new Mesh(meshFiles[i]);

	for (int i = 0; i < TEXTURELIST::NUM_TEXTURES; ++i)
		arr_textures[i] = new Texture(textureFiles[i]);

	for (int i = 0; i < SHADERLIST::NUM_SHADERES; ++i)
		arr_shaders[i] = CreateCustomeShaderByType(to_shaderType(i), shaderFiles[i]);
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

render::Shader * render::RenderManager::CreateCustomeShaderByType(const SHADERLIST & type, const std::string & filename)
{
	switch (type)
	{	
	case SHADERLIST::GENERAL_SHADER:
		return new render::shaders::GeneralShader(filename);
		break;

	case SHADERLIST::NUM_SHADERES:
	default:
		return nullptr;
		break;
	}
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
		arr_shaders[pack.shader_id]->bind();
		boundPack.shader_id = pack.shader_id;
	}
}

void render::RenderManager::updateShader(const ShaderUpdatePack & pack, const SHADERLIST & type)
{
	switch (type)
	{	
	case SHADERLIST::GENERAL_SHADER:
		((render::shaders::GeneralShader*)arr_shaders[type])->update(pack);
		break;

	case SHADERLIST::NUM_SHADERES:
	default:
		break;
	}
}

void render::RenderManager::render(const RenderPack & bind, const ShaderUpdatePack & update)
{
	tryBind(bind);
	updateShader(update, bind.shader_id);

	arr_meshs[bind.mesh_id]->Draw();
}

void render::RenderManager::render(const Drawable & drawable)
{
	render(drawable.renderPack, drawable.updatePack);
}

