#pragma once

//The folliwing exist:
	template class std::vector;

	//These(3) can be bound:
	class Texture;
	class Mesh;
	class Shader;

	//There will be a universial 'Texture' & 'Mesh & 'Shader' array to which each object can index.
	static std::vector<Texture> uni_textures;
	static std::vector<Mesh> uni_meshs;
	static std::vector<Shader> uni_shaders;
	
class Drawable
{
	int texture_ind;//Index to texture in 'uni_textures'.
	int mesh_ind;	//''''''''''''''''''' 'uni_meshs'.
	int shader_ind;	//''''''''''''''''''' 'uni_shaders'.


};
