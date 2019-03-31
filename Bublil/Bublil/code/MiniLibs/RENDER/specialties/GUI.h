#pragma once

#include<GL/glew.h>
#include<string>
#include<glm/glm.hpp>
#include<iostream>
#include"quade.h"

namespace render
{
	namespace specialties
	{
		class GUI
		{
		public:
			GUI() :m_position(0, 0), m_rotation(0,0,0),m_scale(1, 1) {}
			GUI(const std::string& texturefilename, const glm::vec2& position, const glm::vec3& rotation, const glm::vec2& scale);
			~GUI();

			void Bind(unsigned int unit = 0);

			void Draw();
		protected:
		private:
			GLuint m_texture;

			Quade m_quade;

			glm::vec2 m_position;
			glm::vec3 m_rotation;
			glm::vec2 m_scale;
		public:
			glm::vec2& GetPos() { return m_position; }
			glm::vec3& GetRot() { return m_rotation; }
			glm::vec2& GetScale() { return m_scale; }
		
			void setTextureID(const GLuint& texID) { m_texture = texID; }
		};
	}
}
