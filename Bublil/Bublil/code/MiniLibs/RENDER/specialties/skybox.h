#pragma once

#include<string>
#include<vector>

#include"RENDER/core/shader.h"
#include"RENDER/core/camera.h"

#include"RENDER/loading/stb_image.h"
#include"RENDER/core/shaders/skyboxShader.h"

namespace render
{
	namespace specialties
	{
		class Skybox
		{
		public:
			Skybox(const std::string& shader, const std::string& texPath, const std::string& prefix, const std::string& suffix);
			~Skybox();

			void render(const ShaderUpdatePack& pack);
		private:
			void bind();
			void update(const ShaderUpdatePack& pack);
		private:
			Shader * shader;

			GLuint texture;

			GLuint VAO, VBO;
		};
	}
}