#pragma once

#include<GL/glew.h>
#include<string>
#include<glm/glm.hpp>
#include<iostream>
#include"quade.h"

#include"RENDER/loading/stb_image.h"
#include"RENDER/core/shaders/guiShader.h"

namespace render
{
	namespace specialties
	{
		class GUI
		{
		public:
			GUI(const std::string& texturefilename, const glm::vec2& position, const glm::vec2& scale, const std::string& shaderFile);
			~GUI();

			void render();
		protected:
		private:

			void bind(unsigned int unit = 0);

			Shader * shader;

			GLuint m_texture;

			Quade m_quade;

			glm::vec2 m_position;
			glm::vec2 m_scale;
		public:
			glm::vec2& GetPos() { return m_position; }
			glm::vec2& GetScale() { return m_scale; }

			void bindShader() { shader->bind(); }

			void update(const glm::vec2& position, const glm::vec2& scale);
		};
	}
}
